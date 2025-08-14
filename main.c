#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env_copy = copy_env(envp);
	shell.lines = 0;
	shell.exit_status = 0;
	init_builtin(&shell);
	init_signals();

	while (1)
	{
		get_input(&shell);
	}
	return (0);
}
