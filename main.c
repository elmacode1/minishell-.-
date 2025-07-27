#include "minishell.h"

int g_exit_status;

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;
    t_token *head;
    t_cmd *cmd;
	t_all *global;
	
    shell.env_copy = copy_env(envp);
    g_exit_status = 0;
    init_builtin(&shell);
    init_signals();
	global = static_var();
    while(1)
    {
        input = readline("minishell$ ");
        if(!input)
        {
            printf("exit\n");
            exit(1);
        }
        if(*input)
        {
            add_history(input);
	        head = lexer(input);
				// while(head){
				// 	printf("token:%s\n",head->text);
				// 	head=head->next;
				// }
				// exit(0);
            cmd = parsing(head, envp);
			int i=0;
			while(cmd){
				i = 0;
				while(cmd->argv[i]){
					printf("%s\n",cmd->argv[i]);
					i++;
				}
				cmd= cmd->next;
			}
			exit(0);
            g_exit_status = execute(&shell, cmd);
        }
        free(input);
    }
    free_all(global->free_list);
    free(shell.env_copy);
    return 0;
}
