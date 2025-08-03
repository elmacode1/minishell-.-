#include "../minishell.h"

int	string_search(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while(str1[i] == str2[i])
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
	return NULL;
}
int special_char(char *str)
{
	int i = 0;
	if((str[i] == '%' || str[i] == '+') || str[i] == ':' 
	|| str[i] == '/' || str[i] == '.' || str[i] == '=')
		return 1;
	return 0;
}
void expander(t_token **head, t_shell *shell)
{
	t_token *tmp_head;

	tmp_head = *head;
		// 	while(tmp_head){
		// printf("%s\n",tmp_head->text);
		// tmp_head= tmp_head->next;
		// }
		// // exit(0);
	while(tmp_head)
	{
		// if(tmp_head->type == ENV && )
		// 	tmp_head->type = WORD;
		if((tmp_head->type == ENV && !strncmp(tmp_head->text + 1,"",1)) || special_char(tmp_head->text + 1))
			tmp_head->type = WORD;
		if(tmp_head->state != IN_SQUOTE && tmp_head->type == ENV && !strncmp(tmp_head->text + 1,"?",1))
		{
			tmp_head->text = ft_strjoin(ft_itoa(shell->exit_status),tmp_head->text+2);
			tmp_head->type = WORD;
		}
		else if(tmp_head->state != IN_SQUOTE && tmp_head->type == ENV)
		{
			if(get_env_index(tmp_head->text+1,shell->env_copy) >= 0)
				tmp_head->text = get_value(shell->env_copy[get_env_index(tmp_head->text+1,shell->env_copy)]);
			else
				tmp_head->text = ft_strdup("");
			tmp_head->type = WORD;
		}
		else if(tmp_head->state == IN_SQUOTE && tmp_head->type == ENV)
		{
			tmp_head->type = WORD;
		}
		tmp_head = tmp_head->next;
	}
}
