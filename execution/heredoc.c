#include "../minishell.h"

int valid_line(char *line, t_redirect *current)
{
    if(!line)
    {
        ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
        ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
        ft_putstr_fd(current->delimiter, STDERR_FILENO);
        ft_putstr_fd("')\n", STDERR_FILENO);
        return 1;
    }
    else if( strcmp(line, current->delimiter) == 0)
    {
        free(line);
        return 1;
    }
    return 0;

}
void handle_heredoc_child(t_redirect *current, char *tempfile)
{
    int fd;
    char *line;

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
            if(valid_line(line, current) == 1)
                break;
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        close(fd);
}

int check_sig(int status, char *tempfile, int *exit_status, t_redirect *current)
{
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

int heredoc_handeler(t_redirect *current, int *exit_status)
{
    pid_t pid;
    int status;
    char *tempfile;
    static int counter;
    int ret;

    char *id = ft_itoa(counter++);
    tempfile = ft_strjoin("/tmp/tempfile", id); 
    free(id);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if(pid == 0)
    {
        handle_heredoc_child(current, tempfile);
        exit(0);
    }
    else
    { 
        waitpid(pid, &status, 0);
        signal(SIGINT, handle_sigint);
        ret = check_sig(status, tempfile, exit_status, current);
        return ret;
    }
}

