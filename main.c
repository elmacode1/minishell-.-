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
        input = readline("minishell$ ");
        if(!input)
        {
            printf("exit\n");
            exit(1);
        }
        if(*input)
        {
            add_history(input);
            t_command  cmd;
            t_redirect *redir = malloc(sizeof(t_redirect));
            t_redirect *redir2 = malloc(sizeof(t_redirect));
            t_redirect *redir3 = malloc(sizeof(t_redirect));
            //cases to handle
            //redin before heredoc
            //multiple heredocs
            char *args1[] = {"cat", NULL};
            cmd.args = args1;
            cmd.redirs = redir;
            redir->filename = "f3";
            redir->type = RED_IN;
            redir->delimiter = NULL;
            redir->next = redir2;
            redir2->filename = NULL;
            redir2->type = HEREDOC;
            redir2->delimiter = "eof";
            redir2->next = redir3;
            redir3->filename = "out3";
            redir3->type = RED_OUT;
            redir3->next = NULL;
            cmd.next = NULL;

            execute(&shell, &cmd);
            // execute(&shell, &cmd1);
        }
        free(input);
    }
    free(shell.env_copy);
    return 0;
}
