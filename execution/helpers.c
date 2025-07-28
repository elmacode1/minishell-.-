#include "../minishell.h"

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
    // printf("%d", i);
    return 1;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void free_array(char **arr)
{
    int i = 0;

    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}