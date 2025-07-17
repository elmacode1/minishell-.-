#include "../../minishell.h"

char *check_first_arg(char *arg, t_shell *shell)
{
    char *path;

    if(!arg || ft_strcmp(arg, "~") == 0)
    {
        path = get_env_var(shell, "HOME");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            return NULL;
        }
        return path;
    }
    else if(ft_strcmp(arg, "-") == 0)
    {
        path = get_env_var(shell, "OLDPWD");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            return NULL;
        }
        ft_putendl_fd(path, STDOUT_FILENO);
        return path;
    }
    return arg;
}

int ft_cd(t_shell *shell, char **args)
{
    char cwd[1024]; 
    char *path;

    path = check_first_arg(args[1], shell);
    if(!path)
        return 1;
    if(!getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr_fd("minishell: cd: error retreiving current directory\n", STDERR_FILENO);
        return 1;
    }
    if(chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        perror(path);
        return 1;
    }
    set_env_var(shell, "OLDPWD", cwd);
    if(!getcwd(cwd, sizeof(cwd)))
        ft_putstr_fd("minishell: cd: warning: could not update PWD\n", STDERR_FILENO);
    else
        set_env_var(shell, "PWD", cwd);
    return 0;
}

