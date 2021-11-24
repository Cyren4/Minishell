/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_words_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:13 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 15:56:20 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_word(char *cmd)
{
	int	inside;
	int	i;
	int	count;

	i = 0;
	count = 0;
	inside = NO_Q;
	while (cmd && cmd[i])
	{
		while (cmd && cmd[i])
		{
			if ((cmd[i] == '"' && inside != SIMPLE_Q)
				|| (cmd[i] == '\'' && inside != DOUBLE_Q))
				quote_interpretation(cmd[i], &inside);
			if (cmd[i] == ' ' && inside == NO_Q)
				break ;
			i++;
		}
		count++;
		while (cmd && cmd[i] && cmd[i] == ' ')
			i++;
	}
	return (count);
}
