#include "../minishell.h"

int handle_input(t_redirect *current, int *fd_in)
{
    if(current->type == HEREDOC || current->type == RED_IN)
    {
        if(*fd_in != -1)
            close(*fd_in);
        *fd_in = open(current->filename, O_RDONLY);
        if(*fd_in < 0)
        {
            if(access(current->filename, F_OK) != 0)
            {
                print_error("minishell: ", current->filename,": No such file or directory\n");
                return 1;
            }
            if(access(current->filename, X_OK) != 0)
            {
                print_error("minishell: ", current->filename, ": Permission denied\n");
                return 126; 
            }
            return 1;
        }
    }
    return 0;
}

int handle_output(t_redirect *current, int *fd_out)
{
    int flags;
    if(current->type == RED_OUT || current->type == APPEND)
    {
        if(ft_strcmp(current->filename, "/dev/stdout") == 0)
        {
            current = current->next;
            return 0;
        }
        if(*fd_out != -1)
            close(*fd_out);
        if(current->type == RED_OUT)
            flags = O_CREAT | O_WRONLY | O_TRUNC;
        else
            flags = O_CREAT | O_WRONLY | O_APPEND;
        *fd_out = open(current->filename, flags, 0644);
        if(*fd_out < 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(current->filename, STDERR_FILENO);
            ft_putstr_fd(": Permission denied\n", STDOUT_FILENO);
            return 1;
        }
    }
    return 0;
}


void restore_fds(int *fd_in, int *fd_out, int *tmp_in, int *tmp_out)
{
    if(*fd_in != -1)
    {
        dup2(*fd_in, STDIN_FILENO);
        close(*fd_in);
    }
    if(*fd_out != -1)
    {
        dup2(*fd_out, STDOUT_FILENO);
        close(*fd_out);
    }
    if(*tmp_out != -1)
    {
        dup2(*tmp_out, STDOUT_FILENO);
        close(*tmp_out);
    }
    if(*tmp_in != -1)
    {
        dup2(*tmp_in, STDIN_FILENO);
        close(*tmp_in);
    }
}

int check_current(t_redirect *current, int *fd_in, int *fd_out)
{
    int status;
    while (current)
    {
        if((status = handle_input(current, fd_in)) != 0)
            return status;
        else if((status = handle_output(current, fd_out)) != 0)
            return status;
        current = current->next;
    }
    return 0;
}
int    handle_redirections(t_shell *shell, t_cmd *cmd)
{
    int fd_in;
    int fd_out;
    int tmp_out;
    int tmp_in;
    t_redirect *current;

    (void)shell;
    current = cmd->redirections;
    fd_in = -1;
    fd_out = -1;
    int flags;
    tmp_in = -1;
    tmp_out = -1;

    if(!current)
        return 0;
    if(!cmd->argv || !cmd->argv[0])
    {
        tmp_out = dup(STDOUT_FILENO);
        tmp_in = dup(STDIN_FILENO);
    }
    // if((status = check_current(current, &fd_in, &fd_out)) != 0)
    //     return status;
     if(current->type == HEREDOC || current->type == RED_IN)
    {
        if(fd_in != -1)
            close(fd_in);
        fd_in = open(current->filename, O_RDONLY);
        if(fd_in < 0)
        {
            if(access(current->filename, F_OK) != 0)
            {
                print_error("minishell: ", current->filename,": No such file or directory\n");
                return 1;
            }
            if(access(current->filename, X_OK) != 0)
            {
                print_error("minishell: ", current->filename, ": Permission denied\n");
                return 126; 
            }
            return 1;
        }
    }
    if(current->type == RED_OUT || current->type == APPEND)
    {
        if(ft_strcmp(current->filename, "/dev/stdout") == 0)
        {
            current = current->next;
            return 0;
        }
        if(fd_out != -1)
            close(fd_out);
        if(current->type == RED_OUT)
            flags = O_CREAT | O_WRONLY | O_TRUNC;
        else
            flags = O_CREAT | O_WRONLY | O_APPEND;
        fd_out = open(current->filename, flags, 0644);
        if(fd_out < 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(current->filename, STDERR_FILENO);
            ft_putstr_fd(": Permission denied\n", STDOUT_FILENO);
            return 1;
        }
    }
    restore_fds(&fd_in, &fd_out, &tmp_in, &tmp_out);
    return 0;
}


