/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:46:42 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 23:24:45 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*valid_redir(char *cmd, t_gen *data, int i, int el_i)
{
	char	*r_cont;
	int		in;

	in = NO_Q;
	r_cont = malloc(sizeof(char) * (real_size(cmd, data) + 1));
	if (!r_cont)
		return ;
	while (cmd[el_i])
	{
		if (need_interpret_quote(cmd[el_i], in))
			quote_interpretation(cmd[el_i], &in);
		else if (cmd[el_i] == '$' && in != SIMPLE_Q
			&& valid_e(cmd, el_i))
		{
			i += insert_var(r_cont + i, cmd, &el_i, data);
			continue ;
		}
		else
			expand_norm(r_cont, cmd[el_i], &i);
		el_i++;
	}
	r_cont[i] = '\0';
	ft_free(cmd);
	return (r_cont);
}

char	*valid_redir(char *cmd, t_gen *data)
{
	int		el_i;
	int		i;

	i = 0;
	el_i = 0;
	return (valid_redir(cmd, data, i, el_i));
}
