
#include "../minishell.h"

char **copy_env(char **env)
{
    int i;
    char **env_copy;

    i = 0;
    while(env[i])
        i++;
    env_copy = malloc(sizeof(char *) * (i + 1));
    if(!env_copy)
        return NULL;
    i = 0;
    while(env[i])
    {
        env_copy[i] = ft_strdup(env[i]);
        if(!env_copy[i])
        {
            while(i > 0)
                free(env_copy[--i]);
            free(env_copy);
            return NULL;
        }
        i++;
    }
    env_copy[i] = NULL;
    return env_copy;
}

char *get_env_var(t_shell *shell, char *name)
{
    int len;
    int i;

    i = 0;
    len = strlen(name);
    while(shell->env_copy[i])
    {
        if(strncmp(shell->env_copy[i], name, len) == 0 && shell->env_copy[i][len] == '=')
            return (&shell->env_copy[i][len + 1]);
        i++;
    }
    return NULL;
}

int add_new_var(t_shell *shell, char *var)
{
    char **new_env;
    int i;

    i = 0;
    while(shell->env_copy[i])
        i++;
    new_env = malloc((i + 2) * sizeof(char *));
    if(!new_env)
        return -1;
    i = 0;
    while(shell->env_copy[i])
    {
        new_env[i] = strdup(shell->env_copy[i]);
        i++;
    }
    new_env[i] = strdup(var);
    new_env[i + 1] = NULL;
    free(shell->env_copy);
    shell->env_copy = new_env;
    return 0;     
}

int  set_env_var(t_shell *shell, char *name, char *var)
{
    int len;
    int name_len;
    int i;
    char *new_var;

    i = 0;
    name_len = strlen(name);
    len = strlen(name) + strlen(var) + 2;
    new_var = malloc(len);
    if(!new_var)
        return -1;
    new_var = ft_strjoin(name, "=");
    new_var = ft_strjoin(new_var, var);
    while(shell->env_copy[i])
    {
        if(strncmp(shell->env_copy[i], name, name_len) == 0 && shell->env_copy[i][name_len] == '=')
        {
            free(shell->env_copy[i]);
            shell->env_copy[i] = new_var;
            return 0;
        }
        i++;
    }
    add_new_var(shell, new_var);
    return 0;
}

void remove_env_var(t_shell *shell, char *name)
{
    int i;
    int len;
    i = 0;
    len = ft_strlen(name);
    while(shell->env_copy[i])
    {
        if(ft_strncmp(shell->env_copy[i], name, len) == 0 && shell->env_copy[i][len] == '=')
        {
            free(shell->env_copy[i]);
            while(shell->env_copy[i + 1])
            {
                shell->env_copy[i] = shell->env_copy[i + 1];
                i++;
            }
            shell->env_copy[i] = NULL;
            return;
        }
        i++;
    }
}
