#include "minishell.h"

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

char **sorted_env(char **env)
{
    int len;
    int i;
    int j;
    char *temp;
    char **sorted;

    len = 0;
    i = 0;
    j = 0;
    while(env[len])
        len++;
    sorted = copy_env(env);
    while(i < len - 1)
    {
        while(j < len -i - 1)
        {
            if(ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
            {
                temp = env[j];
                env[j] = env[i + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    return sorted;
}


void print_env(char **env)
{
    int i;
    char *equal;
    
    i = 0;
    while(env[i])
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        equal = ft_strchr(env[i], '=');
        if(equal)
        {
            equal = '\0';
            ft_putstr_fd(env[i], STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
            ft_putstr_fd(equal + 1, STDOUT_FILENO);
            ft_putstr_fd("\"\n", STDOUT_FILENO);
            equal = '=';
        }
        else
            ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
}


int ft_export(t_shell *shell, char **args)
{
    int i;
    char **new_env;
    char *new_var;
    char *name;
    char *value;

    i = 1;
    if(!args[1])
    {
        new_env = sorted_env(shell->env_copy);
        print_env(new_env);
        //free_env(new_env);
    }
    while(args[i])
    {
        if(!is_valid(args[i]))
        {
            printf("unvalid identifier\n");
            //adjust it as the bash
            return 1;
        }
        char *equal;
        equal = ft_strchr(args[i], '=');
        if(equal)
        {
            equal = '\0';
            set_env_var(shell, args[i], equal + 1);
            equal = '=';
        }
        else
        {
            if(get_env_var(shell, args[i]))
            {
                
            }
        }
        i++;
    }
    return 0;
}