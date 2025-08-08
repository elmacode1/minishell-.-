#include "../minishell.h"

void	get_input(t_shell *shell)
{
	char	*input;
	t_token	*head;
	t_cmd	*cmd;

	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		exit(1);
	}
	if (*input)
	{
		add_history(input);
		head = lexer(input);
		cmd = parsing(head, shell);
		execute(shell, cmd);
	}
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