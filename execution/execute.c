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

char *get_cmd_path(t_shell *shell, char *cmd)
{
    char *env;
    char **paths;
    char *cmd_path;
    char *result;
    char *slash;
    int i;

    i = 0;
    result = NULL;
    env = get_env_var(shell, "PATH");
    paths = ft_split(env, ':');
    while(paths[i])
    {
        slash = ft_strjoin(paths[i], "/");
        if(ft_strncmp(cmd, "/bin", 4) == 0)
            cmd_path = ft_strjoin(slash, cmd + 4);
        else
            cmd_path = ft_strjoin(slash, cmd);
        if(access(cmd_path, X_OK) == 0)
        {
            result = cmd_path;
            free(slash);
            break;
        }
        free(slash);
        free(cmd_path);
        i++;
    }
    free_array(paths);
    return result;
}

int execute_external(t_shell *shell, t_cmd *cmd)
{
    int pid;
    char *path;
    int status;
    path = get_cmd_path(shell, cmd->argv[0]);
    
    if(!path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(" cmd not found\n", STDERR_FILENO);
        return 127;
    }
    pid = fork();
    if(pid == -1)
    {
        ft_putstr_fd("minishell: fork\n", STDERR_FILENO);
        return 1;
    }
    if(pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if(handle_redirections(shell, cmd) == 1)
        { 
            exit(g_exit_status);
        }
        execve(path, cmd->argv, shell->env_copy);
        ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
        return 126;
    }
    else
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        signal(SIGINT, handle_sigint);
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
        free(path);
        return WEXITSTATUS(status);
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
    if(handle_redirections(shell, cmd) == 1)
    {
        dup2(tmp_out, STDOUT_FILENO);
        dup2(tmp_in, STDIN_FILENO);
        close(tmp_in);
        close(tmp_out);
        return 1;
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
    if(is_builtin(cmd->argv[0]))
        return execute_builtin(shell, cmd);
    else
        return (execute_external(shell, cmd));
}

void open_heredocs(t_cmd *cmd)
{
    t_cmd *temp;
    t_redirect *current;

    temp = cmd;
    while(cmd)
    {
        current = cmd->redirections;
        // if(!current->delimiter)
            // ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
        while (current)
        {
            if(current->type == HEREDOC)
            {
                heredoc_handeler(current);
            }
            current = current->next;
        }
        cmd = cmd->next;
    }
    cmd = temp;
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
        open_heredocs(cmd);
    if(cmd && cmd->argv && cmd->argv[0])
    {
        if(cmd->next)
            g_exit_status = execute_pipes(shell, cmd);
        else
            g_exit_status = execute_cmd(shell, cmd);
    }
    close_heredocs(cmd);
}
