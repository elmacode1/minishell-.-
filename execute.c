#include "minishell.h"

int is_builtin(char *command)
{
    int i;
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    i = 0;
    while(builtins[i])
    {
        if(strcmp(command, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *get_command_path(t_shell *shell, char *cmd)
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
        cmd_path = ft_strjoin(slash, cmd);
        if(access(cmd_path, X_OK) == 0)
        {
            result = cmd_path;
            break;
        }
        free(slash);
        free(cmd_path);
        i++;
    }
    free_array(paths);
    return result;
}

int execute_external(t_shell *shell, t_command *cmd)
{
    int pid;
    char *path;
    int status;
    path = get_command_path(shell, cmd->args[0]);
    if(!path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd("command not found\n", STDERR_FILENO);
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
        handle_redirections(shell, cmd);
        // unlink(shell->tempfile);
        // shell->tempfile = NULL;
        execve(path, cmd->args, shell->env_copy);
        ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
        return 126;
    }
    else
    {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int builtin_func(t_shell *shell, t_command *cmd)
{
    int i;
    char *name;

    i = 0;
    name = cmd->args[0];
    while(shell->builtinds[i].name)
    {
        if(strcmp(shell->builtinds[i].name, name) == 0)
            return(shell->builtinds[i].cmd_func(shell, cmd->args));
        i++;
    }
    return 0;
}

int execute_builtin(t_shell *shell, t_command *cmd)
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
    // unlink(shell->tempfile);
    // shell->tempfile = NULL;
    return status;
}

int execute_command(t_shell *shell ,t_command *cmd)
{
    if(is_builtin(cmd->args[0]))
        return execute_builtin(shell, cmd);
    else
        return (execute_external(shell, cmd));
}

int execute(t_shell *shell, t_command *cmd)
{
    if(cmd->next)
        return execute_pipes(shell, cmd);
    else
        return execute_command(shell, cmd);
}
