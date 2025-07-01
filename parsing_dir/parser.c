#include "minishell.h"
static void add_arg(char ***argv, int *argc, char *arg)
{
    *argv = realloc(*argv, sizeof(char*) * (*argc + 2)); // Reallocate argv to hold one more string (+1 for new, +1 for NULL)
    (*argv)[*argc] = strdup(arg);
    (*argc)++;
    (*argv)[*argc] = NULL;
}
static t_cmd *new_cmd() {
    t_cmd *new;
	new = malloc(sizeof(t_cmd));
    if (!new)
		return NULL;
    new->argv = NULL;
    new->infile = NULL;
    new->outfile = NULL;
    new->append = 0;
    new->next = NULL;
    return new;
}

t_cmd *parse_tokens(t_token *tokens) {
    t_cmd *cmd_head;
	t_cmd *cmd_last;
	t_cmd *curent_cmd;

	cmd_head = NULL;
	cmd_last = NULL;
	curent_cmd = NULL;

    t_token *tok = tokens;
    char **argv = NULL;
    int argc = 0;

    while (tok) {
        if (!curent_cmd) {
            curent_cmd = new_cmd();
            argv = NULL;
            argc = 0;
        }
        if (tok->type == WORD) {
			add_arg(&argv, &argc, tok->text);//adding the arg to the list;
        } else if (tok->type == RED_IN) {
			tok = tok->next;
			if ((tok->next) == NULL)
				return NULL;
            if (tok && tok->type == WORD)
                curent_cmd->infile = ft_strdup(tok->text);
        } else if (tok->type == RED_OUT) {
            tok = tok->next->next;
            if (tok && tok->type == WORD) {
                curent_cmd->outfile = ft_strdup(tok->text);
                curent_cmd->append = 0;
            }
        } else if (tok->type == APPEND) {
            tok = tok->next;
            if (tok && tok->type == WORD) {
                curent_cmd->outfile = ft_strdup(tok->text);
                curent_cmd->append = 1;
            }
        } else if (tok->type == PIPE) {
            curent_cmd->argv = argv;
            argv = NULL;
            argc = 0;
            if (!cmd_head)
                cmd_head = curent_cmd;
            else
                cmd_last->next = curent_cmd;
            cmd_last = curent_cmd;
            curent_cmd = NULL;
        }
        if(tok)
			tok = tok->next;
    }
    //handling last cmd
    if (curent_cmd)
	{
        curent_cmd->argv = argv;
        if (!cmd_head)
            cmd_head = curent_cmd;
        else
            cmd_last->next = curent_cmd;
    }
    return cmd_head;
}