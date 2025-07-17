#include "minishell.h"

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
            t_cmd  cmd;
            t_redirect *redir = malloc(sizeof(t_redirect));
            t_redirect *redir2 = malloc(sizeof(t_redirect));
            t_redirect *redir3 = malloc(sizeof(t_redirect));
            char *args1[] = {"cat", NULL};
            cmd.args = args1;
            cmd.redirs = redir;
            redir->filename = NULL;
            redir->type = HEREDOC;
            redir->delimiter = "eof";
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
        }
        free(input);
    }
    free(shell.env_copy);
    return 0;
}
