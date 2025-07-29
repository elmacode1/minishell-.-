#include "../../minishell.h"

void bubble_sort(char **sorted, int len)
{
    int i;
    int j;
    char *temp;

    i = 0;
    j = 0;
    while(i < len - 1)
    {
        j = 0;
        while(j < len -i - 1)
        {
            if(ft_strcmp(sorted[j], sorted[j + 1]) > 0)
            {
                temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
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

void sort_and_print(char **env)
{
    int len;
    char **sorted;

    len = 0;

    while(env[len])
        len++;
    sorted = copy_env(env);
    bubble_sort(sorted, len);
    print_env(sorted);
    free_env(sorted);
}

void update_env(t_shell *shell, char *equal, char *arg)
{
    char *value;
    if(equal)
    {
        *equal = '\0';
        set_env_var(shell, arg, equal + 1);
        *equal = '=';
    }
    else
    {
        value = get_env_var(shell, arg);
        if(value)
            set_env_var(shell, arg, value);
        else
            add_new_var(shell, arg);
    }
}
int ft_export(t_shell *shell, char **argv)
{
    int i;
    char *equal;
    int ret;

    i = 1;
    ret = 0;
    if(!argv[1])
        sort_and_print(shell->env_copy);
    else
    {
        while(argv[i])
        {
            if(ft_strcmp(argv[i], "") == 0)
                i++;
            else
                break;
        }
        if(argv[i] ==  NULL)
            sort_and_print(shell->env_copy);
    }
    while(argv[i])
    {
        if(!is_valid(argv[i]))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(argv[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            ret = 1;
            i++;
            continue;
        }
        equal = ft_strchr(argv[i], '=');
        update_env(shell, equal, argv[i]);
        i++;
    }
    return ret;
}
