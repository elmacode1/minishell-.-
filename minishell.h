#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

typedef struct s_shell t_shell;

typedef int (*func)(struct s_shell *, char **);

typedef struct s_command
{
    char **args;
    char ***cmds;
    char *infile;
    char *outfile;
    int append;
    int heredoc;
}       t_command;

typedef struct s_buildin
{
    char *name;
    func cmd_func;
}   t_buildin;


struct s_shell
{
    char **env_copy;
    t_buildin buildinds[8];

};
int handle_redirections(t_command *cmd);
int execute_pipes(t_shell *shell, t_command *cmds[]);
char **copy_env(char **env);
void init_buildin(t_shell *shell);
int execute_command(t_shell *shell ,t_command *cmd);
char *get_env_var(t_shell *shell, char *name);
int add_new_var(t_shell *shell, char *var);
int set_env_var(t_shell *shell, char *name, char *var);
char *get_command_path(t_shell *shell, char *cmd);
int is_buildin(char *command);
int execute_buildin(t_shell *shell, t_command *cmd);
int buildins_redirections(t_shell *shell, t_command *cmd);

//testing 
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);



#endif
