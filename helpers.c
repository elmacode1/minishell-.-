#include "minishell.h"

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