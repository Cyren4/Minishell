/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:28:48 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 17:34:23 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	quote_interpretation(char quote, int *inside)
{
	if (quote == '"' && *inside == NO_Q)
		*inside = DOUBLE_Q;
	else if (quote == '\'' && *inside == NO_Q)
		*inside = SIMPLE_Q;
	else if (quote == '\'' && *inside == SIMPLE_Q)
		*inside = NO_Q;
	else if (quote == '"' && *inside == DOUBLE_Q)
		*inside = NO_Q;
}
	// else if ((quote == '"' && *inside == SIMPLE_Q)
	// 		|| (quote == '\'' && *inside == DOUBLE_Q))
	// 		return ;

void	ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}
