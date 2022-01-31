/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:28:57 by vbaron            #+#    #+#             */
/*   Updated: 2022/01/31 20:37:17 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_child(t_gen *data)
{
	(void)data;
	close_pipes(data->ast);
	clean_data(data);
	free_tab(data->cmd_table);
	ft_free(data->cmd);
	clean_envx(data);
	free(data->home);
	ft_free(data->prompt);
}

void	clean_redir(t_gen *data)
{
	close_pipes(data->ast);
	clean_data(data);
	clean_envx(data);
	free(data->home);
	ft_free(data->prompt);
}

void	clean_data(t_gen *data)
{
	if (data->paths != NULL)
		free_tab(data->paths);
	data->ast = NULL;
	data->lex = NULL;
	data->parser.parsed = NULL;
	if (data->status != 1)
	{
		clean_tree(data->ast);
		ft_free(data->pids);
	}
	data->str_err = NULL;
	data->ast = NULL;
	data->pids = NULL;
	data->status = 1;
}

void	delete_data(t_gen *data)
{
	ft_free(data->home);
	ft_free(data->prompt);
	data->lex = NULL;
	clean_env(data);
	if (data->ast != NULL)
		clean_tree(data->ast);
	rl_clear_history();
}

void	clean_exit(t_gen *data)
{
	clean_data(data);
	ft_free(data->home);
	ft_free(data->prompt);
	clean_envx(data);
	rl_clear_history();
}
