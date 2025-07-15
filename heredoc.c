#include "minishell.h"

int heredoc_handeler(t_shell *shell, t_command *cmd)
{
    char *line;
    int fd;
    pid_t pid;
    int status;

    shell->tempfile = "tempfile";
    pid = fork();
    if(pid == 0)
    {
        fd = open(shell->tempfile, O_CREAT | O_APPEND | O_WRONLY, 0666);
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
            if(!line || strcmp(line, cmd->heredoc_delimiter) == 0)
                break;
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        printf("heredoc\n");
        free(line);
        close(fd);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) != 0)
        {
            unlink(shell->tempfile);
            shell->tempfile = NULL;
            return 1;
        }
    }
    cmd->redirs->infiles[0] = strdup(shell->tempfile);
    return 0;

}