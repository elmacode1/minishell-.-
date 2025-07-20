#include "../minishell.h"

int heredoc_handeler(t_redirect *current)
{
    char *line;
    int fd;
    pid_t pid;
    int status;
    char *tempfile;
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    tempfile = ft_strjoin("tempfile",ft_itoa(getpid())); 
    pid = fork();
    if(pid == 0)
    {
       
        fd = open(tempfile, O_CREAT | O_APPEND | O_WRONLY, 0666);
        if(fd < 0)
        {
            ft_putstr_fd("minishell: heredoc\n", STDERR_FILENO);
            return 1;
        }
   
        while(1)
        {
            signal(SIGINT, handle_child_sig);
            signal(SIGQUIT, handle_sigquit);
            line = readline("> ");
            if(!line || strcmp(line, current->delimiter) == 0)
                break;
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        free(line);
        close(fd);
    }
    else
    {
        // signal(SIGINT, SIG_IGN);
        // signal(SIGQUIT, SIG_IGN);
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) != 0)
        {
            unlink(tempfile);
            free(tempfile);
            tempfile = NULL;
            return 1;
        }
    }
    current->filename = strdup(tempfile);
    return 0;

}