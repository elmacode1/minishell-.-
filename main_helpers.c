#include "../minishell.h"

void	get_input(t_shell *shell)
{
	char	*input;
	t_token	*head;
	t_cmd	*cmd;
	t_all	*global;
	
	global = static_var();
	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		free_env(shell->env_copy);
		exit(1);
	}
	if (*input)
	{
		add_history(input);
		head = lexer(input);
		cmd = parsing(head, shell);
		execute(shell, cmd);
	}
	free_all(global->free_list);
	global->free_list = NULL;
	shell->lines++;
	free(input);
}

t_cmd	*parsing(t_token *head, t_shell *shell)
{
    t_cmd *cmd;
    if(!check_errors(head))
        return NULL;
    expander(&head,shell);
    cmd = parse_tokens(head);
    return (cmd);
}