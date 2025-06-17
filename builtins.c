#include "minishell.h"

int ft_echo(t_shell *shell, char **args)
{
    int i;
    int new_line;
    (void)shell;
    char *p;

    i = 1;
    new_line = 1;
    //echo handles -n -n -n or -nnnn so i have to fix it here
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

int ft_cd(t_shell *shell, char **args)
{
    char cwd[1024];
    char oldpwd[1024];
    char *path;

    if(!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd: error retreiving current directory");
        return 1;
    }
    if(!args[1] || ft_strncmp(args[1], "~", 1) == 0)
    {
        path = get_env_var(shell, "HOME");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
            return 1;
        }
    }
    else if(ft_strncmp(args[1], "-", 1) == 0)
    {
        path = get_env_var(shell, "OLDPWD");
        if(!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDOUT_FILENO);
            return 1;
        }
        ft_putendl_fd(path, STDOUT_FILENO);
    }
    else
        path = args[1];
    if(chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: \n", STDOUT_FILENO);
        perror(path);
        return 1;
    }
    set_env_var(shell, "OLDPWD", oldpwd);
    if(!getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr_fd("minishell: cd: error updating PWD\n", STDOUT_FILENO);
        return 0;
    }
    set_env_var(shell, "PWD", cwd);
    return 0;
}


int ft_pwd(t_shell *shell, char **args)
{
    (void)shell;
    (void)args;
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



int ft_unset(t_shell *shell, char **args)
{
    int i;

    i = 1;
    while(args[i])
    {
        if(!is_valid(args[i]))
        {
            ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd(": invalid indentifier\n", STDERR_FILENO);
            return 1;
        }
        remove_env_var(shell, args[i]);
        i++;
    }
    return 0;
}

int ft_env(t_shell *shell, char **args)
{
    int i;

    i = 0;
    if(args[1])
    {
        perror("enter only env without args");
        return 1;
    }
    while(shell->env_copy[i])
    {
        if(strchr(shell->env_copy[i], '='))
            printf("%s\n", shell->env_copy[i]);
        i++;
    }
    return 0;
}

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
        printf("exit : too many arguments\n");
        return 1;
    }
    if(is_num(args[1]) == 0)
    {
        printf("exit : argument must be a number\n");
        exit(255);
    }
    exit_status = atoi(args[1]) % 256;
    exit(exit_status);
    
}


void init_builtin(t_shell *shell)
{
    shell->builtinds[0] = (t_builtin){"echo", &ft_echo};
    shell->builtinds[1] = (t_builtin){"cd", &ft_cd};
    shell->builtinds[2] = (t_builtin){"pwd", &ft_pwd};
    shell->builtinds[3] = (t_builtin){"export", &ft_export};
    shell->builtinds[4] = (t_builtin){"unset", &ft_unset};
    shell->builtinds[5] = (t_builtin){"env", &ft_env};
    shell->builtinds[6] = (t_builtin){"exit", &ft_exit};
    shell->builtinds[7] = (t_builtin){NULL, NULL};
}