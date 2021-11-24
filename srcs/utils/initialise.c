/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:36:52 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/24 18:17:59 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialise_pids(t_gen *data, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		data->pids[i] = 0;
		i++;
	}
}

void	init_data(t_gen *data)
{
	data->prompt = ft_strdup("minishell $ ");
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->env = NULL;
	data->lex = NULL;
	data->prev_token = -1;
	data->status = 1;
	data->exit_stat = 0;
	data->home = NULL;
	data->paths = NULL;
	data->ast = NULL;
	data->str_err = NULL;
	data->pids = NULL;
	data->cmd_table = NULL;
	data->cmd = NULL;
	data->redirs.start = NULL;
	data->redirs.end = NULL;
	data->redirs.redir_count = 0;
}
