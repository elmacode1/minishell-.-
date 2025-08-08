#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_all *global;

	(void)ac;
	(void)av;
	global = static_var();
	shell.env_copy = copy_env(envp);
	shell.lines = 0;
	shell.exit_status = 0;
	init_builtin(&shell);
	init_signals();
	while (1){
		get_input(&shell);
		free_all(&global->free_list);
	}
	free(shell.env_copy);
	return (0);
}
