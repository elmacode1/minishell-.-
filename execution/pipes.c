#include "../minishell.h"

int **create_pipes(int n_cmds)
{
    int j;
    int **pipes;

    j = 0;
    pipes = malloc(sizeof(int *) * (n_cmds - 1));
    if(!pipes)
        return NULL;
    while(j < n_cmds - 1)
    {
        pipes[j] = malloc(sizeof(int *) * 2);
        if(!pipes[j])
            return NULL;
        if(pipe(pipes[j]) == -1)
        {
            perror("pipe failes\n");
            return NULL;
        }
        j++;
    }
    return pipes;
}

void free_pipes(int  **pipes, int n_cmds)
{
    int j;

    j = 0;
    while(j < n_cmds - 1)
    {
        free(pipes[j]);
        j++;
    }
    free(pipes);
}

void waiting_all(int n_cmds)
{
    int j;

    j = 0;
    while(j < n_cmds)
    {
        wait(NULL);
        j++;
    }
}

int builtin_exec_pipe(t_shell *shell, char **args)
{
    int i;
    char *name;

    i = 0;
    name = args[0];
    while(shell->builtinds[i].name)
    {
        if(strcmp(shell->builtinds[i].name, name) == 0)
            return(shell->builtinds[i].cmd_func(shell, args));
        i++;
    }
    return 0;
}

int count_cmds(t_cmd *cmd)
{
    int n_cmds;

    n_cmds = 0;
    while(cmd)
    {
        n_cmds++;
        cmd = cmd->next;
    }
    return n_cmds;
}

int execute_pipes(t_shell *shell, t_cmd *cmd)
{
    int n_cmds;
    int i;
    int j;
    int pid;
    int **pipes;
    char *path;

    i = 0;
    n_cmds = count_cmds(cmd);
    printf("%d\n", n_cmds);
    pipes = create_pipes(n_cmds);
    while(i < n_cmds)
    {
        j = 0;
        
        pid = fork();
        if(pid == 0)
        {
            signal(SIGINT, handle_child_sig);
            signal(SIGQUIT, handle_sigquit);
            if(i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if(i < n_cmds - 1)
                dup2(pipes[i][1], STDOUT_FILENO);
            while(j < n_cmds - 1)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            if(is_builtin(cmd->args[0]))
                return execute_builtin(shell, cmd);
            else
            {
                path = get_cmd_path(shell, cmd->args[0]);
                if(!path)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    ft_putstr_fd(cmd->args[0], STDERR_FILENO);
                    ft_putstr_fd("cmd not found\n", STDERR_FILENO);
                    return 127;
                }
                handle_redirections(shell, cmd);
                execve(path, cmd->args, shell->env_copy);
                free(path);
                ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
                return 126;
            }
        }
        cmd = cmd->next;
        i++;
    }
    j = 0;
    while(j < n_cmds - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    waiting_all(n_cmds);
    free_pipes(pipes, n_cmds);
    return 0;
}
