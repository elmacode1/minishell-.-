#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include "Libft/libft.h"

typedef struct s_shell t_shell;

typedef int (*func)(struct s_shell *, char **);

typedef struct  s_redirects
{
    char **infiles;
    char **outfiles;
    int append[1024];
    // char **heredoc_delimiter;

}   t_redirects;

typedef struct s_command
{
    char **args;
    // char *infile;
    // char *outfile;
    // int append;
    char *heredoc_delimiter;
    t_redirects *redirs;
    struct s_command *next;
}       t_command;

// malaks structures
// typedef struct s_redirect {
//     char         *filename;
//     int type;                  // RED_IN,  RED_OUT,  APPEND,  HEREDOC
//     struct s_redirect          *next;
// } t_redirect;

// typedef struct s_cmd {
//     char          **argv;
//     t_redirect            *redirections;       // this is the linked list of all redirections
//     struct s_cmd            *next;
// } t_cmd;
//handle multiple redirections

typedef struct s_builtin
{
    char *name;
    func cmd_func;
}   t_builtin;

struct s_shell
{
    char **env_copy;
    t_builtin builtinds[8];
    char *tempfile;
    volatile __sig_atomic_t in_heredoc;
    volatile __sig_atomic_t child_pid;
    int exit_status;
};

typedef struct s_signal
{
    int in_heredoc;
    pid_t heredoc_pid;
} t_signal;

extern t_signal g_signal;


int handle_redirections(t_shell *shell, t_command *cmd);
int execute_pipes(t_shell *shell, t_command *cmd);
char **copy_env(char **env);
void init_builtin(t_shell *shell);
int execute_command(t_shell *shell ,t_command *cmd);
char *get_env_var(t_shell *shell, char *name);
int add_new_var(t_shell *shell, char *var);
int set_env_var(t_shell *shell, char *name, char *var);
char *get_command_path(t_shell *shell, char *cmd);
int is_builtin(char *command);
int execute_builtin(t_shell *shell, t_command *cmd);
int heredoc_handeler(t_shell *shell, t_command *cmd);
void remove_env_var(t_shell *shell, char *name);
int is_valid(char *var);
int ft_export(t_shell *shell, char **args);
int ft_cd(t_shell *shell, char **args);
int ft_echo(t_shell *shell, char **args);
int ft_env(t_shell *shell, char **args);
int ft_exit(t_shell *shell, char **args);
int ft_pwd(t_shell *shell, char **args);
int ft_unset(t_shell *shell, char **args);
int	ft_strcmp(const char *s1, const char *s2);
void free_array(char **arr);
int builtin_func(t_shell *shell, t_command *cmd);
int execute(t_shell *shell, t_command *cmd);
void init_signals(void);
void handle_heredoc_sig(int sig);
void handle_sigint(int sig);
void handle_sigquit(int sig);

#endif
