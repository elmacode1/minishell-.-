#include "minishell.h"

int heredoc_handeler(t_redirect *current)
{
    char *line;
    int fd;
    pid_t pid;
    int status;
    char *tempfile;

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
        signal(SIGINT, handle_heredoc_sig);
        signal(SIGQUIT, handle_sigquit);
        while(1)
        {
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
        signal(SIGINT, SIG_IGN);
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
    // current->type = RED_IN;
    // fd = open(shell->tempfile, O_RDONLY);
    // if(fd < 0)
    //     return 1;
    // dup2(fd, STDIN_FILENO);
    // close(fd);
    return 0;

}