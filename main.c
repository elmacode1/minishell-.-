#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;
    // t_token *head;
	// t_all *global;
	t_cmd *cmd;

    shell.env_copy = copy_env(envp);
    init_builtin(&shell);
    init_signals();
    while(1)
    {
        input = readline("minishell$ ");
        if(!input)
        {
            printf("exit\n");
            exit(1);
        }
        // if(!strcmp(str,"exit"))
		// {
		// 	free_all(global->free_list);
		// 	free(str);
		// 	exit(0);
		// }
        if(*input)
        {
            add_history(input);
            // cmd = parsing(head,str,env);
            execute(&shell, cmd);
        }
        free(input);
    }
    // free_all(global->free_list);
    free(shell.env_copy);
    return 0;
}
