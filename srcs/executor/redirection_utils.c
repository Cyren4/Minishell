/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:46:42 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 12:39:07 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*valid_redir(char *cmd, t_gen *data)
{
	char	*r_cont;
	int		el_i;
	int		i;
	int		in;

	i = 0;
	el_i = 0;
	in = NO_Q;
	r_cont = malloc(sizeof(char) * (real_size(cmd, data) + 1));
	if (!r_cont)
		return ;
	while (cmd[el_i])
	{
		if ((cmd[el_i] == '"' && in != SIMPLE_Q)
			|| (cmd[el_i] == '\'' && in != DOUBLE_Q))
			quote_interpretation(cmd[el_i], &in);
		else if (cmd[el_i] == '$' && in != SIMPLE_Q
			&& valid_e(cmd, el_i))
		{
			i += insert_var(r_cont + i, cmd, &el_i, data);
			continue ;
		}
		else
		{
			r_cont[i] = cmd[el_i];
			i++;
		}
		el_i++;
	}
	r_cont[i] = '\0';
	ft_free(cmd);
	return (r_cont);
}
