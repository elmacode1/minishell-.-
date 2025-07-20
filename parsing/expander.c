#include "../minishell.h"
int	string_search(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while(str1[i]==str2[i])
	{
		if(!str1[i+1] && str2[i+1] == '=')
			return 1;
		i++;
	}

	return 0;
}

int get_env_index(char *str, char **env)
{
	int i;
	i = 0;

	while(env[i])
	{
		if(string_search(str,env[i]))
			return i;
		i++;
	}
	return (-1);
}
char *get_value(char *str)
{
	int i;
	i = 0;

	while(str[i])
	{
		if(str[i] == '=')
			return ft_strdup(&str[i+1]);
		i++;
	}
}
void expander(t_token **head,char **env)
{
	t_token *tmp_head;
	tmp_head = *head;

	while(tmp_head)
	{
		if(tmp_head->state != IN_SQUOTE && tmp_head->type == ENV)
		{
			tmp_head->text = get_value(env[get_env_index(tmp_head->text+1,env)]);
			tmp_head->type=WORD ;
		}
		tmp_head= tmp_head->next;
	}
}
