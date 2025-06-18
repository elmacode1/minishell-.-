#include "minishell.h"
int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
int is_special(char c)
{
	if (c == '|' || c == '<' || c == '>'|| c == '\n'
		|| c == '\'' || c == '\"' || c == '$' || is_space(c))
		return (1);
	return (0);
}