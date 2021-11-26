/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/26 15:01:16 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\"' || end[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*end_sin_quote(char *end)
{
	char	*tmp;

	tmp = strdup_sin_quote(end);
	free(end);
	return (tmp);
}

void	count_redirs(t_gen *data, t_lexer *redirs)
{
	t_lexer	*head;

	data->redirs.redir_count = 0;
	head = redirs;
	while (head->next != NULL)
	{
		if (head->token == LT2)
			data->redirs.redir_count++;
		head = head->next;
	}
}

char	*expand_redir(t_gen *data, t_lexer *fd)
{
	char	*tmp;

	fd->content = expand_elem(fd, data);
	tmp = strdup_sin_quote(fd->content);
	free(fd->content);
	return (tmp);
}
