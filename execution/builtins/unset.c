#include "../../minishell.h"

int ft_unset(t_shell *shell, char **args)
{
    int i;
    int ret;

    i = 1;
    ret = 0;
    while(args[i])
    {
        if(!is_valid(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
        }
        else
            remove_env_var(shell, args[i]);
        i++;
    }
    return ret;
}