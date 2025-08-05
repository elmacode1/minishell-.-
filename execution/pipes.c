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
        pipes[j] = malloc(sizeof(int ) * 2);
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

void waiting_all(int n_cmds, t_shell *shell, int *pids)
{
    int j;
    int status;
    int pid;

    j = 0;
    while(j < n_cmds)
    {
        pid = waitpid(pids[j], &status, 0);
        j++;
    }
    if(pid != -1)
    {
        if(WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
        if(WIFSIGNALED(status))
        {
            if(WTERMSIG(status) == SIGQUIT)
            ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
            else if(WTERMSIG(status) == SIGINT)
            ft_putstr_fd("\n", STDERR_FILENO);
            shell->exit_status = 128 + WTERMSIG(status);
        }
    }
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

int builtin_exec_pipe(t_shell *shell, char **argv)
{
    int i;
    char *name;

    i = 0;
    name = argv[0];
    while(shell->builtinds[i].name)
    {
        if(strcmp(shell->builtinds[i].name, name) == 0)
            return(shell->builtinds[i].cmd_func(shell, argv));
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
void close_pipes(int n_cmds, int **pipes)
{
    int j;

    j = 0;
    while(j < n_cmds - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
}
void manage_pipes(int i, int **pipes, int n_cmds)
{
    int j;

    j = 0;
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
}

void manage_cmd(t_cmd *cmd, t_shell *shell, int tmp_in, int tmp_out, char *path)
{
    int status;

    if(!cmd->argv || !cmd->argv[0])
    {
        shell->exit_status = handle_redirections(shell, cmd);
        exit(shell->exit_status);
    }
    else
    {
        if(is_builtin(cmd->argv[0]))
        {
            shell->exit_status = execute_builtin(shell, cmd);
            exit(shell->exit_status);
        }
        else
        {
            if((status = validate_arg(cmd, tmp_in, tmp_out, &path, shell)) != -1)
                exit(status);
            execve(path, cmd->argv, shell->env_copy);
            free(path);
            ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
            exit(126);
        }
    }
}


void init_vars(t_cmd *cmd, t_pipes *pipe)
{
    pipe->i = 0;
     pipe->tmp_out = dup(STDOUT_FILENO);
     pipe->tmp_in = dup(STDIN_FILENO);
     pipe->path = NULL;
     pipe->n_cmds = count_cmds(cmd);
     pipe->pipes = create_pipes( pipe->n_cmds);
     pipe->pids = malloc(sizeof(int) * pipe->n_cmds);
}

int execute_pipes(t_shell *shell, t_cmd *cmd)
{
    t_pipes *pipe;

    pipe = malloc(sizeof(t_pipes));
    init_vars(cmd, pipe);
    while(pipe->i < pipe->n_cmds)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        pipe->pid = fork();
        if(pipe->pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            manage_pipes(pipe->i,pipe->pipes, pipe->n_cmds);
            manage_cmd(cmd, shell, pipe->tmp_in, pipe->tmp_out, pipe->path);
        }
        cmd = cmd->next;
        pipe->pids[pipe->i] = pipe->pid;
        pipe->i++;
    }
    close_pipes(pipe->n_cmds, pipe->pipes);
    waiting_all(pipe->n_cmds, shell, pipe->pids);
    free_pipes(pipe->pipes, pipe->n_cmds);
    return shell->exit_status;
}
