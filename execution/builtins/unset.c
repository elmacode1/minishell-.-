#include "../../minishell.h"

int ft_unset(t_shell *shell, char **argv)
{
    int i;
    int ret;

    i = 1;
    ret = 0;
    while(argv[i])
    {
        if(!is_valid(argv[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(argv[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
        }
        else
            remove_env_var(shell, argv[i]);
        i++;
    }
    return ret;
}