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

typedef enum e_token_type{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	APPEND,
	SQUOTE,
	DQUOTE,
	WHITESPACE,
	HEREDOC,
	NEW_LINE,
	ENV,
}t_tokentype;

extern int g_exit_status;

typedef struct s_redirect {
    char         *filename;
    int type;
    char *delimiter;
    struct s_redirect          *next;
} t_redirect;

typedef struct s_cmd
{
    char **argv; 
    t_redirect *redirections; 
    struct s_cmd *next;
}       t_cmd;

typedef struct s_builtin
{
    char *name;
    func cmd_func;
}   t_builtin;

struct s_shell
{
    char **env_copy;
    t_builtin builtinds[8];
    int exit_status;
	int lines;
};

//malak structs


typedef	enum s_state{
	GENERAL,
	IN_DQUOTE,
	IN_SQUOTE,
} t_state;



typedef struct s_free
{
	void *content;
	struct s_free *next;
} t_free;

typedef struct s_token
{
	char *text;
	t_tokentype type;
	t_state state;
	struct s_token *next;
}	
t_token;

typedef struct s_all
{
	t_token *token;
	t_cmd *cmd;
	t_free *free_list;
}t_all;

int handle_redirections(t_shell *shell, t_cmd *cmd);
int execute_pipes(t_shell *shell, t_cmd *cmd);
char **copy_env(char **env);
void init_builtin(t_shell *shell);
int execute_cmd(t_shell *shell ,t_cmd *cmd);
char *get_env_var(t_shell *shell, char *name);
int add_new_var(t_shell *shell, char *var);
int set_env_var(t_shell *shell, char *name, char *var);
char *get_cmd_path(t_shell *shell, char *cmd);
int is_builtin(char *cmd);
int execute_builtin(t_shell *shell, t_cmd *cmd);
int heredoc_handeler(t_redirect *current);
void remove_env_var(t_shell *shell, char *name);
int is_valid(char *var);
int ft_export(t_shell *shell, char **argv);
int ft_cd(t_shell *shell, char **argv);
int ft_echo(t_shell *shell, char **argv);
int ft_env(t_shell *shell, char **argv);
int ft_exit(t_shell *shell, char **argv);
int ft_pwd(t_shell *shell, char **argv);
int ft_unset(t_shell *shell, char **argv);
int	ft_strcmp(const char *s1, const char *s2);
void free_array(char **arr);
int builtin_func(t_shell *shell, t_cmd *cmd);
void execute(t_shell *shell, t_cmd *cmd);
void init_signals(void);
void handle_child_sig(int sig);
void handle_sigint(int sig);
void handle_sigquit(int sig);
void close_heredocs(t_cmd *cmd);

// malak s functions

t_token *lexer(char *str);
int is_space(char c);
int is_special(char c);
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstlast_token(t_token *lst);
t_token	*ft_lstnew_token(char *text,t_state state,t_tokentype  type);
int count_word(char *s);
char *ft_getword(char *s);
char *get_env(char *s);
// t_all *static_var();
int check_errors(t_token *tokens);
t_token *lst_skip_spaces(t_token *token);
t_cmd *parse_tokens(t_token *tokens);

void	add_arg(char ***argv, int *argc, char *arg);
t_cmd	*new_cmd();
void	add_redirection(t_cmd *cmd, char *filename, int type);
t_cmd *parse_tokens(t_token *tokens);
t_free *free_lst_new(void *content);
t_free	*free_lstlast(t_free *node);
void	free_lstadd_back(t_free **node, t_free *new);
t_all *static_var();
void free_all(t_free *node);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
t_cmd	*parsing(t_token *head, char **env);
void expander(t_token **head,char **env);
void free_helper(void *ptr);

#endif







