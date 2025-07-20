#include "../minishell.h"

void handle_child_sig(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", STDOUT_FILENO);
    exit(130);
}

void handle_sigint(int sig)
{
    (void)sig;

    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
    exit(131);
}


void init_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);

}

