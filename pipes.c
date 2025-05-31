#include "minishell.h"

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

int execute_pipes(t_shell *shell, t_command *cmds[])
{
    int n_cmds;
    int i;
    int j;
    int pid;
    int **pipes;
    char *path;

    n_cmds = 0;
    i = 0;
    while(cmds[n_cmds])
        n_cmds++;
    pipes = create_pipes(n_cmds);
    while(i < n_cmds)
    {
        j = 0;
     
        pid = fork();
        if(pid == 0)
        {
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
            if(is_buildin(cmds[i]->args[0]))
            {
                execute_buildin(shell, cmds[i]);
                exit(0);
            }
            else
            {
                path = get_command_path(shell, cmds[i]->args[0]);
                execve(path, cmds[i]->args, shell->env_copy);
                perror("execve");
                exit(1);
            }
        }
        i++;
    }
    j = 0;
    while(j < n_cmds - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    j = 0;
    while(j < n_cmds)
    {
        wait(NULL);
        j++;
    }
    return 0;
}