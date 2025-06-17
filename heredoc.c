#include "minishell.h"

int heredoc_handeler(t_command *cmd)
{
    char *line;
    int fd;
    char *tmp;

    tmp = "tempfile";
    fd = open(tmp, O_CREAT | O_APPEND | O_WRONLY, 0666);
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
    cmd->infile = strdup(tmp);
    return 0;
}
