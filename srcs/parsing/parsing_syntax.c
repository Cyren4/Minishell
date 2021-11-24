/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:39:40 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 17:10:28 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(int token)
{
	return (token == LT || token == GT || token == LT2 || token == GT2);
}

char	*get_token(int token)
{
	if (token == PIPE)
		return ("|");
	else if (token == LT)
		return ("<");
	else if (token == LT2)
		return ("<<");
	else if (token == GT)
		return (">");
	else if (token == GT)
		return (">>");
	return ("newline");
}

int	check_syntax(t_lexer *lex)
{
	t_lexer	*tmp;
	int		ret;

	tmp = lex;
	ret = -1;
	if (lex != NULL && lex->token == PIPE)
		ret = PIPE;
	while (tmp && ret == -1)
	{
		if (tmp->token == PIPE && (tmp->next == NULL
				|| tmp->next->token == PIPE))
			ret = PIPE;
		else if (is_redir(tmp->token) && tmp->next != NULL
			&& is_redir(tmp->next->token))
			ret = tmp->token;
		else if (is_redir(tmp->token) && tmp->next == NULL)
			ret = 8;
		tmp = tmp->next;
	}
	if (ret != -1)
		print_error("bash: syntax error near unexpected token `",
			get_token(ret), "\'\n");
	return (ret);
}
