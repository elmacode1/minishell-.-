#include "minishell.h"

int    handle_redirections(t_shell *shell, t_command *cmd)
{
    int fd;
    int flags;
    
    if(cmd->heredoc_delimiter)
        heredoc_handeler(shell, cmd);
    if(cmd->infile) 
    {
        fd = open(cmd->infile, O_RDONLY);
        if(fd < 0)
            return 1;
        dup2(fd, STDIN_FILENO);
        
        close(fd);
    }
    else if(cmd->outfile)
    {
        flags = O_CREAT | O_WRONLY;
        if(cmd->append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
        fd = open(cmd->outfile, flags, 0644);
        if(fd < 0)
            return 1;
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    unlink(shell->tempfile);
    shell->tempfile = NULL;
    return 0;
}


