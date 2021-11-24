/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:28:57 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/24 16:29:14 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_child(t_gen *data)
{
	close_pipes(data->ast);
	clean_data(data);
	free_tab(data->cmd_table);
	free(data->cmd);
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
	clean_tree(data->ast);
	if (data->paths != NULL)
		free_tab(data->paths);
	data->ast = NULL;
	data->lex = NULL;
	free(data->parser.std_in);
	free_tab(data->parser.parsed);
	data->parser.parsed = NULL;
	data->ast = NULL;
	data->str_err = NULL;
	data->status = 1;
	free(data->pids);
}

void	delete_data(t_gen *data)
{
	ft_free(data->home);
	ft_free(data->prompt);
	data->lex = NULL;
	clean_env(data);
	if (data->ast != NULL)
		clean_tree(data->ast);
	clear_history();
}

void	clean_exit(t_gen *data)
{
	clean_data(data);
	ft_free(data->home);
	ft_free(data->prompt);
	clean_envx(data);
	clear_history();
}
