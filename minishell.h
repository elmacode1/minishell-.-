/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:26:42 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 17:28:57 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_shell	t_shell;

typedef int				(*t_func)(struct s_shell *, char **);

typedef enum e_token_type
{
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
	EMPTY_STR,
}						t_tokentype;

typedef struct s_redirect
{
	char				*filename;
	int					type;
	char				*delimiter;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**argv;
	t_redirect			*redirections;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_builtin
{
	char				*name;
	t_func				cmd_func;
}						t_builtin;

struct					s_shell
{
	char				**env_copy;
	t_builtin			builtinds[8];
	int					exit_status;
	int					lines;
};

typedef struct s_tmp
{
	int					tmp_in;
	int					tmp_out;
}						t_tmp;

typedef struct s_pipes
{
	int					n_cmds;
	int					i;
	int					pid;
	int					**pipes;
	char				*path;
	t_tmp				*tmp;
	int					*pids;
}						t_pipes;

typedef struct s_extern_cmd
{
	int					pid;
	char				*path;
	int					status;
	t_tmp				*tmp;
}						t_extern_cmd;

typedef struct s_heredoc
{
	pid_t				pid;
	char				*tempfile;
	char				*id;
}						t_heredoc;

//parsing structs
typedef enum s_state
{
	GENERAL,
	IN_DQUOTE,
	IN_SQUOTE,
}						t_state;

typedef struct s_free
{
	void				*content;
	struct s_free		*next;
}						t_free;

typedef struct s_token
{
	char				*text;
	t_tokentype			type;
	t_state				state;
	struct s_token		*next;
}						t_token;

typedef struct s_all
{
	t_token				*token;
	t_cmd				*cmd;
	t_free				*free_list;
}						t_all;

int						handle_redirections(t_cmd *cmd);
int						execute_pipes(t_shell *shell, t_cmd *cmd);
char					**copy_env(char **env);
void					init_builtin(t_shell *shell);
int						execute_cmd(t_shell *shell, t_cmd *cmd);
char					*get_env_var(t_shell *shell, char *name);
int						add_new_var(t_shell *shell, char *var);
int						set_env_var(t_shell *shell, char *name, char *var);
char					*get_cmd_path(t_shell *shell, char *cmd);
int						is_builtin(char *cmd);
int						execute_builtin(t_shell *shell, t_cmd *cmd);
int						heredoc_handeler(t_redirect *current, int *status);
void					remove_env_var(t_shell *shell, char *name);
int						is_valid(char *var);
int						ft_export(t_shell *shell, char **argv);
int						ft_cd(t_shell *shell, char **argv);
int						ft_echo(t_shell *shell, char **argv);
int						ft_env(t_shell *shell, char **argv);
int						ft_exit(t_shell *shell, char **argv);
int						ft_pwd(t_shell *shell, char **argv);
int						ft_unset(t_shell *shell, char **argv);
int						ft_strcmp(const char *s1, const char *s2);
void					free_array(char **arr);
int						builtin_func(t_shell *shell, t_cmd *cmd);
void					execute(t_shell *shell, t_cmd *cmd);
void					init_signals(void);
void					handle_child_sig(int sig);
void					handle_sigint(int sig);
void					handle_sigquit(int sig);
void					close_heredocs(t_cmd *cmd);
int						valid_cmd(t_shell *shell, t_cmd *cmd, char **path);
void					print_error(char *ms1, char *arg, char *ms2);
int						validate_arg(t_cmd *cmd, t_tmp *tmp, char **path,
							t_shell *shell);
int						execute_builtin(t_shell *shell, t_cmd *cmd);
int						execute_external(t_shell *shell, t_cmd *cmd);
char					*path_access(char **paths, char *cmd);
char					*get_cmd_path(t_shell *shell, char *cmd);
void					print_error(char *ms1, char *arg, char *ms2);
int						is_directory(char *path);
int						valid_cmd(t_shell *shell, t_cmd *cmd, char **path);
int						is_builtin(char *cmd);
int						**create_pipes(int n_cmds);
void					free_pipes(t_pipes *pipe);
void					waiting_all(int n_cmds, t_shell *shell, int *pids);
int						builtin_exec_pipe(t_shell *shell, char **argv);
int						count_cmds(t_cmd *cmd);
void					print_error(char *ms1, char *arg, char *ms2);
void					bubble_sort(char **sorted, int len);
void					print_env(char **env);
void					free_env(char **env);
int						compose_varname(char **new_var, int len, char *name,
							char *var);
int						check_access_redir(t_redirect *current);
void					exetern_part(t_cmd *cmd, t_pipes *pipe, t_shell *shell,
							t_all *g);
void					init_heredoc(t_heredoc *heredoc);

// free funcs
t_free					*free_lst_new(void *content);
t_free					*free_lstlast(t_free *node);
void					free_lstadd_back(t_free **node, t_free *new);
void					free_all(t_free **node);
void					free_helper(void *ptr);

// utils
int						is_space(char c);
int						is_special(char c);
char					*ft_strdup(const char *s1);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
t_token					*lst_skip_spaces(t_token *token);
t_all					*static_var(void);
void					get_input(t_shell *shell);

// errors funcs
int						check_errors(t_token *tokens);

// lexer funcs
void					ft_lstadd_back_token(t_token **lst, t_token *new);
t_token					*ft_lstlast_token(t_token *lst);
t_token					*ft_lstnew_token(char *text, t_state state,
							t_tokentype type);
int						count_word(char *s);
char					*ft_getword(char *s);
char					*get_env(char *s);
void					quotes_handler(char *c, t_state *state, t_token **head);
void					lexer_special(char *str, int *i, t_state *state,
							t_token **head);
t_token					*lexer(char *str);

// expander funcs
int						string_search(const char *str1, const char *str2);
int						get_env_index(char *str, char **env);
char					*get_value(char *str);
int						special_char(char *str);
void					expander(t_token **head, t_shell *shell);

// parser funcs
int						count_tokens(t_token *tokens);
t_cmd					*ft_lstlast_cmd(t_cmd *lst);
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd					*new_cmd(void);
void					add_redirection(t_cmd *cmd, char *filename, int type);
void					append_token_text(char **tmp, t_token **tokens);
void					parse_inside_quotes(char **tmp, t_token **tokens,
							t_tokentype quote);
void					parse_next_word(char **tmp, t_token **tokens);
int						parse_word_group(t_token **tokens, char **argv);
int						is_redirect_token(t_token *t);
char					*parse_quoted_redirect(t_token **tokens);
char					*redirect_target(t_token **tokens);
void					parse_redirect(t_token **tokens, t_cmd *cmd);
t_cmd					*parse_tokens(t_token *tokens);
t_cmd					*parsing(t_token *head, t_shell *shell);
char					*ft_strdup2(const char *str);
#endif
