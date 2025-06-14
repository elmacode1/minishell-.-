#include"minishell.h"

void analyze(){
	t_all *test;

	test=static_var();
	t_token *tmp = test->tokens;
		while (tmp)
		{
			printf("Token: %-10s  Type: %d\n", tmp->text, tmp->type);
			tmp = tmp->next;
		}

}