#include "../minishell.h"

int ft_echo(t_shell *shell, char **args)
{
    int i;
    int new_line;
    (void)shell;
    char *p;

    i = 1;
    new_line = 1;
    while(args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        p = args[i] + 2;
        while(*p == 'n')
            p++;
        if(*p != '\0')
            break;
        new_line = 0;
        i++;
    }
    while(args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if(args[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if(new_line)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return 0;
}
