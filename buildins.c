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
    char cwd[1024];

    if(getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return 0;
    }
    else
    {
        perror("pwd\n");
        return 1;
    }
    
}

int ft_unset(t_shell *shell, char **args)
{
    int size;
    char **new_env;
    int i;
    int j;
    int k;
    int len;

    k = 1;
    while(args[k])
    {
        i = 0;
        j = 0;
        size = 0;
        len = strlen(args[k]);
        while(shell->env_copy[size])
            size++;
        new_env = malloc((size + 1) * sizeof(char *));
        while(shell->env_copy[i])
        {
            if(strncmp(shell->env_copy[i], args[k], len) == 0 )
            {
                i++;
                free(shell->env_copy[i]);
                continue;
            }
            new_env[j] = strdup(shell->env_copy[i]);
            i++;
            j++;
        }
        k++;
        new_env[j] = NULL;
        free(shell->env_copy);
        shell->env_copy = new_env;
    }
    return 0;
}

char *get_name(char *full_var)
{
    int i;
    char *name;

    i = 0;
    while(full_var[i] && full_var[i] != '=')
        i++;
    name = malloc(i + 1);
    name = strncpy(name, full_var, i);
    name[i] = '\0';
    return name;
}

char *get_value(char *full_var)
{
    int i;

    i = 0;
    while(full_var[i] != '=')
        i++;
    if(!full_var[i])
        return NULL;
    return strdup(&full_var[i  + 1]);
}

int simple_export(t_shell *shell, char **args)
{
    int i;
    char *name;
    char *value;

    i = 0;

    while(shell->env_copy[i])
    {
        name = get_name(shell->env_copy[i]);
        value = get_value(shell->env_copy[i]);
        printf("declare -x %s=\"%s\"\n", name, value);
        free(name);
        free(value);
        i++;
    }
    return 0;
}

int is_valid(char *var)
{
    int i;

    i = 0;
    if(!var || !(*var) || (!isalpha(*var) && *var != '_'))
        return 0;
    while(var[i] && var[i] != '=')
    {
        if(!isalnum(var[i]) && var[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

int ft_export(t_shell *shell, char **args)
{
    int i;
    char *new_var;
    char *name;
    char *value;

    i = 1;
    if(!args[1])
        simple_export(shell, args);
    while(args[i])
    {
        if(!is_valid(args[i]))
        {
            printf("unvalid identifier\n");
            return 1;
        }
        else if(strchr(args[i], '=') != 0)
        {
            name = get_name(args[i]);
            value= get_value(args[i]);
            set_env_var(shell, name, value);
            free(name);
            free(value);
        }
        else
        {
            if(get_env_var(shell, args[i]))
            {
                new_var = strdup(args[i]);
                add_new_var(shell, new_var);
            }
        }
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
    int exit_status;
    printf("called\n");
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