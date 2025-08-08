/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:47:38 by mael-gho          #+#    #+#             */
/*   Updated: 2025/08/08 21:59:53 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getword(char *s)
{
	int		c;
	char	*str;

	c = count_word(s);
	str = malloc(sizeof(char) * (c + 1));
	free_helper(str);
	ft_strlcpy(str, s, c + 1);
	return (str);
}

char	*get_env(char *s)
{
	int		c;
	char	*str;

	c = count_word(s + 1);
	str = malloc(sizeof(char) * (c + 2));
	free_helper(str);
	ft_strlcpy(str, s, c + 2);
	return (str);
}
