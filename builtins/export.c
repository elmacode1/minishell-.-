#include "../minishell.h"

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
        j = 0;
        while(j < len -i - 1)
        {
            if(ft_strncmp(sorted[j], sorted[j + 1], ft_strlen(sorted[j])) > 0)
            {
                temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
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
            *equal = '\0';
            ft_putstr_fd(env[i], STDOUT_FILENO);
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(equal + 1, STDOUT_FILENO);
            ft_putstr_fd("\"\n", STDOUT_FILENO);
            *equal = '=';
        }
        else
            ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
}

void free_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

int ft_export(t_shell *shell, char **args)
{
    int i;
    char **new_env;
    char *equal;
    char *value;
    int ret;

    i = 1;
    ret = 0;
    if(!args[1])
    {
        new_env = sorted_env(shell->env_copy);
        print_env(new_env);
        free_env(new_env);
    }
    while(args[i])
    {
        if(!is_valid(args[i]))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
            i++;
            continue;
        }
        equal = ft_strchr(args[i], '=');
        if(equal)
        {
            *equal = '\0';
            set_env_var(shell, args[i], equal + 1);
            *equal = '=';
        }
        else
        {
            value = get_env_var(shell, args[i]);
            if(value)
                set_env_var(shell, args[i], value);
            else
                add_new_var(shell, args[i]);
        }
        i++;
    }
    return ret;
}