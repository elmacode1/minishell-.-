#include "minishell.h"

int    handle_redirections(t_shell *shell, t_command *cmd)
{
    int fd[1024];
    int flags;
    int i;
    
    i = 0;
    if(cmd->heredoc_delimiter)
    {
        if(heredoc_handeler(shell, cmd) == 1)
            return 1;
    }
    if(cmd->redirs->infiles)
    {
        while(cmd->redirs->infiles[i])
        {
            fd[i] = open(cmd->redirs->infiles[i], O_RDONLY);
            if(fd[i] < 0)
                return 1;
            if(cmd->redirs->infiles[i + 1])
                close(fd[i]);
            i++;
        }
        dup2(fd[i - 1], STDIN_FILENO);
        close(fd[i - 1]);
    }
    i = 0;   
    if(cmd->redirs->outfiles)
    {
        while (cmd->redirs->outfiles[i])
        {
            flags = O_CREAT | O_WRONLY;
            if(cmd->redirs->append[i] == 1)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;
            fd[i] = open(cmd->redirs->outfiles[i], flags, 0644);
            if(fd[0] < 0)
                return 1;
            if(cmd->redirs->outfiles[i + 1])
                close(fd[i]);
            i++;
        }
        dup2(fd[i - 1], STDOUT_FILENO);
        close(fd[i - 1]);
    }
    unlink(shell->tempfile);
    shell->tempfile = NULL;
    return 0;
}


