#include "minishell.h"


int ft_echo(t_shell *shell, char **args)
{
    int i;
    int new_line;
    (void*)shell;

    i = 1;
    new_line = 1;
    if(args[1] && strcmp(args[1], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while(args[i])
    {
        printf("%s", args[i]);
        if(args[i + 1])
            printf(" ");
        i++;
    }

    if(new_line)
        printf("\n");
    return 0;
}

int ft_cd(t_shell *shell, char **args)
{
    char cwd[1024];
    char *oldpwd;
    char *path;

    if(!getcwd(cwd, sizeof(cwd)))
    {
        perror("cd");
        return 1;
    }
    if(!args[1] || (args[1] && strcmp(args[1], "~") == 0))
    {
        path = get_env_var(shell, "HOME");
         if(!path)
        {
            perror("home not set");
            return 1;
        }
    }
    else if(args[1] && strcmp(args[1], "-") == 0)
    {
        path = get_env_var(shell, "OLDPWD");
        if(!path)
        {
            perror("oldpwd not set");
            return 1;
        }
        printf("%s", path);
    }
    else
        path = args[1];
    if(chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }
    set_env_var(shell, "OLDPWD", cwd);
    if(getcwd(cwd, sizeof(cwd)))
        set_env_var(shell, "PWD", cwd);
    return 0;
}


int ft_pwd(t_shell *shell, char **args)
{
    
}int ft_unset(t_shell *shell, char **args)
{
    
}int ft_export(t_shell *shell, char **args)
{
    
}int ft_env(t_shell *shell, char **args)
{
    
}int ft_exit(t_shell *shell, char **args)
{
    
}


void init_buildin(t_shell *shell)
{
    shell->buildinds[0] = (t_buildin){"echo", &ft_echo};
    shell->buildinds[1] = (t_buildin){"cd", &ft_cd};
    shell->buildinds[2] = (t_buildin){"pwd", &ft_pwd};
    shell->buildinds[3] = (t_buildin){"export", &ft_export};
    shell->buildinds[4] = (t_buildin){"unset", &ft_unset};
    shell->buildinds[5] = (t_buildin){"env", &ft_env};
    shell->buildinds[6] = (t_buildin){"exit", &ft_exit};
    shell->buildinds[7] = (t_buildin){NULL, NULL};
}