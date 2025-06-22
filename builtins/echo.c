#include "../minishell.h"

int check_new_line(char **args)
{
    int i;
    char *p;

    i = 1;
    while(args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        p = args[i] + 2;
        while(*p == 'n')
            p++;
        if(*p != '\0')
            break;
        i++;
    }
    return i;
}

int ft_echo(t_shell *shell, char **args)
{
    int i;
    (void)shell;


    i = 1;
    i = check_new_line(args);
    while(args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if(args[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if(check_new_line(args) == 1)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return 0;
}
