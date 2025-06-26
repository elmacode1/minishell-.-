#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;

    shell.env_copy = copy_env(envp);
    init_builtin(&shell);
    
    while(1)
    {
        input = readline("minishell$");
        if(!input)
        {
            printf("exit\n");
            exit(1);
        }
        if(*input)
        {
            add_history(input);
            t_command  cmd;
            // t_command cmd1;
            // t_command cmd2;
        
            char *args1[] = {"echo", NULL};
            // char *args2[] = {"export", NULL};

            // char *args2[] = {"sort", NULL};
            // char *args3[] = {"uniq", NULL};

            cmd.args = args1;
            cmd.outfile = NULL;
            cmd.infile = NULL;
            cmd.heredoc_delimiter = "oum";
            cmd.append = 0;
            cmd.next = NULL;

            // cmd1.args = args2;
            // cmd1.outfile = NULL;
            // cmd1.infile = NULL;
            // cmd1.heredoc_delimiter = 0;
            // cmd1.append = 0;
            // cmd1.next = &cmd2;

            // cmd2.args = args3;
            // cmd2.outfile = "test3.txt";
            // cmd2.infile = NULL;
            // cmd2.heredoc_delimiter = 0;
            // cmd2.append = 0;
            // cmd2.next = NULL;
            execute(&shell, &cmd);
            // execute(&shell, &cmd1);
        }
        free(input);
    }
    free(shell.env_copy);
    return 0;
}