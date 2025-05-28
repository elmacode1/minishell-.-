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
            char *args[] = {"cd", "~", NULL};
            cmd.args = args;
            execute_command(&shell, &cmd);
        }
        free(input);
    
    }
    return 0;
}