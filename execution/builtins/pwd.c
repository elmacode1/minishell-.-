#include "../../minishell.h"

int ft_pwd(t_shell *shell, char **argv)
{
    (void)shell;
    (void)argv;
    char cwd[1024];
    char *pwd;

    if(getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return 0;
    }
    pwd = get_env_var(shell, "PWD");
    if(pwd)
    {
        ft_putendl_fd(pwd, STDOUT_FILENO);
        return 0;
    }
    ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
    perror("");
    return 1;
}
