#include "../minishell.h"

int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    i = 0;
    while(builtins[i])
    {
        if(strcmp(cmd, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *path_access(char **paths, char *cmd)
{
    char *slash;
    char *cmd_path;

    int i;

    i = 0;
    while(paths[i])
    {
        slash = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(slash, cmd);
        if(access(cmd_path, X_OK) == 0)
        {
            free(slash);
            return cmd_path;
        }
        free(slash);
        free(cmd_path);
        i++;
    }
    return NULL;
}

char *get_cmd_path(t_shell *shell, char *cmd)
{
    char *env;
    char **paths;
    char *result;

    result = NULL;
    env = get_env_var(shell, "PATH");
    paths = ft_split(env, ':');
    result = path_access(paths,cmd);
    free_array(paths);
    return result;
}

void print_error(char *ms1, char *arg, char *ms2)
{
    ft_putstr_fd(ms1, STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(ms2, STDERR_FILENO);
}

int valid_cmd(t_shell *shell, t_cmd *cmd, char **path)
{
    if(cmd->argv[0][0] == '/' || (cmd->argv[0][0] == '.' && cmd->argv[0][1] == '/'))
    {
        if(access(cmd->argv[0], F_OK) != 0)
        {
            print_error("minishell: ", cmd->argv[0],": No such file or directory\n");
            return 127;
        }
        if(access(cmd->argv[0], X_OK) != 0)
        {
            print_error("minishell: ", cmd->argv[0],": Permission denied\n");
            return 126; 
        }
        *path = ft_strdup(cmd->argv[0]);
    }
    else
    {
        *path = get_cmd_path(shell, cmd->argv[0]);
    
        if(!*path)
        {
            print_error("minishell: ", cmd->argv[0],": cmd not found\n");
            return 127;
        }
    }
    return 0;
}
int restore_tmp(int tmp_in, int tmp_out, int stat)
{
    dup2(tmp_in, STDIN_FILENO);
    dup2(tmp_out, STDOUT_FILENO);
    close(tmp_out);
    close(tmp_in);
    return(stat);
}

int handle_parent_sig(int status, int pid, int tmp_in, int tmp_out)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    signal(SIGINT, handle_sigint);

    dup2(tmp_in, STDIN_FILENO);
    dup2(tmp_out, STDOUT_FILENO);
    close(tmp_out);
    close(tmp_in);
    if(WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    {
        ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
        return 131;
    }
    else if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        ft_putstr_fd("\n", STDERR_FILENO);
        return 130; 
    }
    // free(path);
    return WEXITSTATUS(status);
}
int validate_arg(t_cmd *cmd, int tmp_in, int tmp_out, char **path, t_shell *shell)
{
    int status;

    if(ft_strcmp(cmd->argv[0], "") == 0)
        return 0;
    if((shell->exit_status = handle_redirections(shell, cmd)) != 0)
    {
        dup2(tmp_in, STDIN_FILENO);
        dup2(tmp_out, STDOUT_FILENO);
        close(tmp_out);
        close(tmp_in);
        return shell->exit_status;
    }
    status = valid_cmd(shell, cmd, path);
    if(status != 0)
    {
        dup2(tmp_in, STDIN_FILENO);
        dup2(tmp_out, STDOUT_FILENO);
        close(tmp_out);
        close(tmp_in);
        return status;
    }
    return -1;
}
void handle_child(t_cmd *cmd, t_shell *shell, char *path)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execve(path, cmd->argv, shell->env_copy);
    ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
}

int execute_external(t_shell *shell, t_cmd *cmd)
{
    int pid;
    char *path;
    int status;
    int ret;
    
    int tmp_out = dup(STDOUT_FILENO);
    int tmp_in = dup(STDIN_FILENO);
    path = NULL;
    status = 0;
    
    if((ret = validate_arg(cmd, tmp_in, tmp_out, &path, shell)) != -1)
        return ret;
    pid = fork();
    if(pid == 0)
    {
        handle_child(cmd, shell, path);
        exit(126);
    }
    else
    {
        ret = handle_parent_sig(status, pid, tmp_in, tmp_out);
        free(path);
        return ret;
    }
}

int builtin_func(t_shell *shell, t_cmd *cmd)
{
    int i;
    char *name;

    i = 0;
    name = cmd->argv[0];
    while(shell->builtinds[i].name)
    {
        if(strcmp(shell->builtinds[i].name, name) == 0)
            return(shell->builtinds[i].cmd_func(shell, cmd->argv));
        i++;
    }
    return 0;
}

int execute_builtin(t_shell *shell, t_cmd *cmd)
{
    int tmp_out;
    int tmp_in;
    int status;

    tmp_out = dup(STDOUT_FILENO);
    tmp_in = dup(STDIN_FILENO);
    if((status = handle_redirections(shell, cmd)) != 0)
    {
        dup2(tmp_out, STDOUT_FILENO);
        dup2(tmp_in, STDIN_FILENO);
        close(tmp_in);
        close(tmp_out);
        return status;
    }
    status = builtin_func(shell, cmd);
    dup2(tmp_out, STDOUT_FILENO);
    dup2(tmp_in, STDIN_FILENO);
    close(tmp_in);
    close(tmp_out);
    return status;
}

int execute_cmd(t_shell *shell ,t_cmd *cmd)
{
    if(!cmd->argv || !cmd->argv[0])
        return handle_redirections(shell,cmd);
    if(is_builtin(cmd->argv[0]))
        return execute_builtin(shell, cmd);
    else
        return (execute_external(shell, cmd));
}

int open_heredocs(t_cmd *cmd, t_shell *shell)
{
    t_cmd *temp;
    t_redirect *current;

    temp = cmd;
    while(cmd)
    {
        current = cmd->redirections;
        while (current)
        {
            if(current->type == HEREDOC)
            {
                if(heredoc_handeler(current, &shell->exit_status) == 130)
                {
                    shell->exit_status = 130;
                    return 130;
                }
            }
            current = current->next;
        }
        cmd = cmd->next;
    }
    cmd = temp;
    return 0;
}

void close_heredocs(t_cmd *cmd)
{
    t_cmd *temp;
    t_redirect *current;

    temp = cmd;
    while(cmd)
    {
        current = cmd->redirections;
        while (current)
        {
            if(current->type == HEREDOC && current->filename)
            {
                unlink(current->filename);
                free(current->filename);
                current->filename = NULL;
            }
            current = current->next;
        }
        cmd = cmd->next;
    }
    cmd = temp;
}

void execute(t_shell *shell, t_cmd *cmd)
{
    if(cmd)
        if(open_heredocs(cmd, shell) == 130)
            return;
    if(cmd )
    {
        if(cmd->next)
            shell->exit_status = execute_pipes(shell, cmd);
        else
            shell->exit_status = execute_cmd(shell, cmd);
    }
    close_heredocs(cmd);
}
// handle redirections should happen even if there is no command file should be opened
