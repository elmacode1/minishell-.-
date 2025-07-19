#include "minishell.h"

// void	add_arg(char ***argv, int *argc, char *arg)
// {
//     *argv = realloc(*argv, sizeof(char*) * (*argc + 2)); // Reallocate argv to hold one more string (+1 for new, +1 for NULL)
//     (*argv)[*argc] = strdup(arg);
//     (*argc)++;
//     (*argv)[*argc] = NULL;
// }
// t_cmd	*new_cmd() 
// {
//     t_cmd *new;
// 	new = malloc(sizeof(t_cmd));
//     if (!new)
// 		return NULL;
//     new->argv = NULL;
// 	new->redirections = NULL;
//     new->next = NULL;
//     return new;
// }

// void	add_redirection(t_cmd *cmd, char *filename, int type)
// {
// 	// Create new redirection node
// 	t_redirect *new_redirect;
// 	new_redirect = malloc(sizeof(t_redirect));
// 	new_redirect->filename = strdup(filename);
// 	new_redirect->type = type;
// 	new_redirect->next = NULL;

// // Add to the end of the list
// 	if (!cmd->redirections)
// 	{
// 		cmd->redirections = new_redirect;
// 	}
// 	else
// 	{
// 		t_redirect *last = cmd->redirections;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new_redirect;
// 	}
// }