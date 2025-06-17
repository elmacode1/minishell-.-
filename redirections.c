#include "minishell.h"

int handle_redirections(t_command *cmd)
{
    int fd;
    int flags;
    
    if(cmd->heredoc_delimiter)
        heredoc_handeler(cmd);
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
    return 0;
}

int builtins_redirections(t_command *cmd)
{
    int tmp_out;
    int tmp_in;

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
    dup2(tmp_out, STDOUT_FILENO);
    dup2(tmp_in, STDIN_FILENO);
    close(tmp_in);
    close(tmp_out);
    return 0;
}