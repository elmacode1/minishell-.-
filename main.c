#include "minishell.h"



// void aff_lexer(t_token *head)
// {
// 	t_token *tmp=head;
// 	while(tmp){
// 		printf("token%s.\n",tmp->text);
// 		tmp = tmp->next;
// 	}
// }
// void aff_cmd(t_cmd *cmd){
// 	 	while (cmd)
//         {
//             // Print cmd arguments
//             if (cmd->argv)
//             {
//                 int i = 0;
//                 while (cmd->argv[i])
//                 {
//                     printf("arg[%d] == %s\n", i, cmd->argv[i]);
//                     i++;
//                 }
//             }
            
//             // Print redirections
//             t_redirect *redirect = cmd->redirections;
//             while (redirect)
//             {
//                 printf("redirection: %s (type: %d)(delimiter: %s)\n", redirect->filename, redirect->type,redirect->delimiter);
//                 redirect = redirect->next;
//             }
            
//             cmd = cmd->next;
//         }
// }
int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;
    t_token *head;
	t_all *global;
	t_cmd *cmd;

    shell.env_copy = copy_env(envp);
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
        if(!strcmp(input,"exit"))
		{
			free_all(global->free_list);
			free(input);
			exit(0);
		}
        if(*input)
        {
            add_history(input);
	        head = lexer(input);
			// aff_lexer(head);
            if((cmd = parsing(head, envp))){
           aff_cmd(cmd);
			execute(&shell, cmd);
			}
        }
        free(input);
    }
    free_all(global->free_list);
    free(shell.env_copy);
    return 0;
}
