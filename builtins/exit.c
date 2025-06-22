#include "../minishell.h"

int is_num(char *str)
{
    int i;
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_exit(t_shell *shell, char **args)
{
    (void)shell;
    int exit_status;
    if (!args[1])
        exit(0);
    if(args[2])
    {
        ft_putstr_fd("minishell: exit : too many arguments\n", STDERR_FILENO);
        return 1;
    }
    if(is_num(args[1]) == 0)
    {
        ft_putstr_fd("minishell: exit: `", STDERR_FILENO);
        ft_putstr_fd(args[1],STDERR_FILENO);
        ft_putstr_fd("' numeric argument required\n", STDERR_FILENO);
        exit(255);
    }
    exit_status = atoi(args[1]) % 256;
    exit(exit_status);
}
