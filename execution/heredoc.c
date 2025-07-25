#include "../minishell.h"

int heredoc_handeler(t_redirect *current)
{
    char *line;
    int fd;
    pid_t pid;
    int status;
    char *tempfile;
    static int counter;


    char *id = ft_itoa(counter++);
    tempfile = ft_strjoin("/tmp/tempfile", id); 
    free(id);
    printf("%s\n", tempfile);
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
            g_exit_status = 130;
            return 1;
        }
        if(WEXITSTATUS(status) != 0)
        {
            unlink(tempfile);
            free(tempfile);
            tempfile = NULL;
            return 1;
        }
    }
    
    current->filename = strdup(tempfile);
    free(tempfile);
    return 0;
}