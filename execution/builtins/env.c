#include "../../minishell.h"

int ft_env(t_shell *shell, char **argv)
{
    int i;

    i = 0;
    if(argv[1])
    {
        ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
        return 1;
    }
    while(shell->env_copy[i])
    {
        if(strchr(shell->env_copy[i], '='))
            ft_putendl_fd(shell->env_copy[i], STDOUT_FILENO);
        i++;
    }
    return 0;
}