#include "minishell.h"

t_signal g_signal = {0};

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *input;
    t_shell shell;

    shell.env_copy = copy_env(envp);
    init_builtin(&shell);
    init_signals();
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
            t_redirects *redir = malloc(sizeof(t_redirects));
            redir->infiles = malloc(sizeof(char *) * 3);
            redir->outfiles = malloc(sizeof(char *) * 3);
            // redir->append = malloc(sizeof(int *) * 3);
            // t_command cmd1;
            // t_command cmd2;
        
            char *args1[] = {"cat", NULL};
            // char *args2[] = {"pwd", NULL};

            // char *args2[] = {"sort", NULL};
            // char *args3[] = {"uniq", NULL};

            cmd.args = args1;
            // redir->outfiles = NULL;
            redir->infiles[0] = "f1";
            redir->infiles[1] = "f3";
            redir->infiles[2] = NULL;
            // redir->append = NULL;
            redir->outfiles[0] = "out1";
            redir->outfiles[1] = "out2";
            redir->outfiles[2] = NULL;

            redir->append[0] = 1;
            redir->append[1] = 1;
            redir->append[2] = '\0';
            cmd.redirs = redir; 
            cmd.heredoc_delimiter = NULL;
            // cmd.append = 0;
            cmd.next = NULL;

            // cmd1.args = args2;
            // cmd1.outfile = NULL;
            // cmd1.infile = NULL;
            // cmd1.heredoc_delimiter = 0;
            // cmd1.append = 0;
            // cmd1.next = NULL;

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