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
    int i;

    i = 0;
    env = get_env_var(shell, "PATH");
    paths = ft_split(env, ':');
    while(paths[i])
    {
        cmd_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
        if(access(cmd_path, X_OK) == 0)
            return(cmd_path);
        free(cmd_path);
        i++;
    }
    return NULL;
}

int execute_external(t_shell *shell, t_command *cmd)
{
    int pid;
    char *path;
    int status;

    path = get_command_path(shell, cmd->args[0]);
    pid = fork();
    if(pid == -1)
    {
        perror("fork\n");
        return 1;
    }
    if(pid == 0)
    {
        handle_redirections(cmd);
        execve(path, cmd->args, shell->env_copy);
        perror("execve failed\n");
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int execute_builtin(t_shell *shell, t_command *cmd)
{
    int i;
    char *name;
    int cmd_len;
    int len;

    i = 0;
    name = cmd->args[0];
    len = strlen(name);
    while(shell->builtinds[i].name)
    {
        cmd_len = strlen(shell->builtinds[i].name);
        if(strncmp(shell->builtinds[i].name, name, len) == 0 && len == cmd_len)
        {
            return(shell->builtinds[i].cmd_func(shell, cmd->args));
        }
        i++;
    }
    return 0;
}



int execute_command(t_shell *shell ,t_command *cmd)
{
    int tmp_out;
    int tmp_in;
    int status;
    if(is_builtin(cmd->args[0]))
    { 

        tmp_out = dup(STDOUT_FILENO);
        tmp_in = dup(STDIN_FILENO);
        if(handle_redirections(cmd) == 1)
        {
            dup2(tmp_out, STDOUT_FILENO);
            dup2(tmp_in, STDIN_FILENO);
            close(tmp_in);
            close(tmp_out);
            return 1;
        }
        status = execute_builtin(shell, cmd);
        dup2(tmp_out, STDOUT_FILENO);
        dup2(tmp_in, STDIN_FILENO);
        close(tmp_in);
        close(tmp_out);
        return (status);
    }
    else
        return (execute_external(shell, cmd));
}