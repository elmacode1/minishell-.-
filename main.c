#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;

    shell.env_copy = copy_env(envp);
    init_buildin(&shell);
    
    while(1)
    {
        input = readline("minishell$");
        if(!input)
        {
            printf("exit\n");
            exit;
        }
        if(*input)
        {
            add_history(input);
            t_command  cmd;
            t_command  cmd1;
            t_command  cmd2;
        
            char *args[] = {"echo", "hello", NULL};
            char *args1[] = {"wc", "", NULL};
            //char *args2[] = {"uniq", NULL};
            cmd.args = args;
            cmd1.args = args1;
           // cmd2.args = args2;
            t_command *cmds[] = {&cmd, &cmd1, NULL};
            // cmds[0] = args;
            // cmds[1] = args1;
            
            execute_pipes(&shell, cmds);

            // printf("%s\n", get_env_var(&shell ,"hey_hey"));
         
            // cmd1.args = args1;
            // execute_command(&shell, &cmd);
            //execute_command(&shell, &cmd1);
        }
        free(input);
    }
    return 0;
}