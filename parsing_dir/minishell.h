#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft_malak/libft.h"

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

typedef struct s_cmd {
    char **argv;        // Command and its arguments (e.g., {"ls", "-l", NULL})
    char *infile;       // Input file for '<' (e.g., "input.txt")
    char *outfile;      // Output file for '>' or '>>' (e.g., "output.txt")
    int   append;       // 1 if '>>', 0 if '>'
    struct s_cmd *next; // Next command in a pipeline (for '|')
} t_cmd;

typedef struct s_free
{
	void *content;
	struct s_free *next;
} t_free;

typedef struct s_token
{
	char *text;
	t_tokentype type;
	struct s_token *next;
}	
t_token;

typedef struct s_all
{
	t_free *free_list;
	t_token *tokens;
}t_all;

int is_space(char c);
int is_special(char c);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(char *text, t_tokentype  type);
int count_word(char *s);
int check_squotes(t_token *token);
int check_dquotes(t_token *token);
char *ft_getword(char *s);
char *get_env(char *s);
t_all *static_var();


#endif
