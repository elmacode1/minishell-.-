#include "../minishell.h"

int    handle_redirections(t_shell *shell, t_cmd *cmd)
{
    int fd_in;
    int fd_out;
    int flags;
    t_redirect *current;

    (void)shell;
    current = cmd->redirs;
    fd_in = -1;
    fd_out = -1;
    if(!current)
        return 0;
    while (current)
    {
        if(current->type == HEREDOC)
        {
            if(fd_in != -1)
                close(fd_in);
            if(heredoc_handeler(current) == 1)
                return 1;
            fd_in = open(current->filename, O_RDONLY);
            if(fd_in < 0)
                return 1;
        }
        else if(current->type == RED_IN)
        {
            if(fd_in != -1)
                close(fd_in);
            fd_in = open(current->filename, O_RDONLY);
            if(fd_in < 0)
                return 1;
        }
        else if(current->type == RED_OUT || current->type == APPEND)
        {
            if(fd_out != -1)
                close(fd_out);
            if(current->type == RED_OUT)
                flags = O_CREAT | O_WRONLY | O_TRUNC;
            else
                flags = O_CREAT | O_WRONLY | O_APPEND;
            fd_out = open(current->filename, flags, 0644);
            if(fd_out < 0)
                return 1;
        }
        current = current->next;
    }
    if(fd_in != -1)
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if(fd_out != -1)
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    current = cmd->redirs;
    while(current)
    {
        if(current->type == HEREDOC && current->filename)
        {
            unlink(current->filename);
            free(current->filename);
            current->filename = NULL;
        }
        current = current->next;
    }
    return 0;
}


