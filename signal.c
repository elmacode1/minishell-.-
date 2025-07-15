#include "minishell.h"

void handle_heredoc_sig(int sig)
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
    // shell->exit_status = 131;
}

// void handle_childsig(t_shell *shell, int sig)
// {
//     (void)sig;
//     int status;
//     pid_t pid;

//     while((pid = waitpid(-1, &status, WNOHANG)) > 0)
//     {

//     }
// }


void init_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);

}

