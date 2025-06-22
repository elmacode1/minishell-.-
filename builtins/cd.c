#include "../minishell.h"

int ft_cd(t_shell *shell, char **args)
{
    char cwd[1024];
    char oldpwd[1024];
    char *path;

    if(!getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr_fd("minishell: cd: error retreiving current directory\n", STDERR_FILENO);
        return 1;
    }
    if(!args[1] || ft_strncmp(args[1], "~", 1) == 0)
    {
        path = get_env_var(shell, "HOME");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            return 1;
        }
    }
    else if(ft_strncmp(args[1], "-", 1) == 0)
    {
        path = get_env_var(shell, "OLDPWD");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            return 1;
        }
        ft_putendl_fd(path, STDOUT_FILENO);
    }
    else
        path = args[1];
    if(chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: \n", STDERR_FILENO);
        ft_putendl_fd(path, STDERR_FILENO);
        return 1;
    }
    set_env_var(shell, "OLDPWD", oldpwd);
    if(!getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr_fd("minishell: cd: error updating PWD\n", STDERR_FILENO);
        return 1;
    }
    else
        set_env_var(shell, "PWD", cwd);
    return 0;
}