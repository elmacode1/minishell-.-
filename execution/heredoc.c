#include "../minishell.h"

int heredoc_handeler(t_redirect *current, int *exit_status)
{
    char *line;
    int fd;
    pid_t pid;
    int status;
    char *tempfile;
    static int counter;
    int pipe_fd[2];
    
    pipe(pipe_fd);
    char *id = ft_itoa(counter++);
    tempfile = ft_strjoin("/tmp/tempfile", id); 
    free(id);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if(pid == 0)
    {
        fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
        if(fd < 0)
        {
            ft_putstr_fd("minishell: heredoc\n", STDERR_FILENO);
            exit(1);
        } 
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        while(1)
        {
            line = readline("> ");
            if(!line)
            {
                ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
                ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
                ft_putstr_fd(current->delimiter, STDERR_FILENO);
                ft_putstr_fd("')\n", STDERR_FILENO);
                // lines++;
                break;
            }
            else if( strcmp(line, current->delimiter) == 0)
            {
                free(line);
                break;
            }
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        close(fd);
        exit(0);
    }
    else
    { 
        waitpid(pid, &status, 0);
        signal(SIGINT, handle_sigint);
        if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            ft_putstr_fd("\n", STDOUT_FILENO);
            unlink(tempfile);
            free(tempfile);
            *exit_status = 130;
            return 130;
        }
        current->filename = strdup(tempfile);
        free(tempfile);
        return 0;
    }
}
