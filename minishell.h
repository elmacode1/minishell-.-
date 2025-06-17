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
#include "Libft/libft.h"

typedef struct s_shell t_shell;

typedef int (*func)(struct s_shell *, char **);

typedef struct s_command
{
    char **args;
    char ***cmds;
    char *infile;
    char *outfile;
    int append;
    char *heredoc_delimiter;
}       t_command;

typedef struct s_builtin
{
    char *name;
    func cmd_func;
}   t_builtin;


struct s_shell
{
    char **env_copy;
    t_builtin builtinds[8];

};
int handle_redirections(t_command *cmd);
int execute_pipes(t_shell *shell, t_command *cmds[]);
char **copy_env(char **env);
void init_builtin(t_shell *shell);
int execute_command(t_shell *shell ,t_command *cmd);
char *get_env_var(t_shell *shell, char *name);
int add_new_var(t_shell *shell, char *var);
int set_env_var(t_shell *shell, char *name, char *var);
char *get_command_path(t_shell *shell, char *cmd);
int is_builtin(char *command);
int execute_builtin(t_shell *shell, t_command *cmd);
int builtins_redirections(t_command *cmd);
int heredoc_handeler(t_command *cmd);
void remove_env_var(t_shell *shell, char *name);
int is_valid(char *var);




#endif
