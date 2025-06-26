#include "minishell.h"

int heredoc_handeler(t_shell *shell, t_command *cmd)
{
    char *line;
    int fd;

    shell->tempfile = "tempfile";
    fd = open(shell->tempfile, O_CREAT | O_APPEND | O_WRONLY, 0666);
    if(fd < 0)
    {
        ft_putstr_fd("minishell: heredoc\n", STDERR_FILENO);
        return 1;
    }
    while(1)
    {
        line = readline("> ");
        if(!line || strcmp(line, cmd->heredoc_delimiter) == 0)
            break;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }

    free(line);
    close(fd);
    cmd->infile = strdup(shell->tempfile);

    return 0;
}