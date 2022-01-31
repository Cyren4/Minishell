/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2022/01/31 20:37:07 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_display(t_gen *data)
{
	printf("\b\b  \b\bexit\n");
	ft_free(data->home);
	ft_free(data->prompt);
	free(data->parser.std_in);
	clean_envx(data);
	rl_clear_history();
	exit(get_exit_stat(-1));
}

void	display_prompt(t_gen *data)
{
	get_pid(1);
	data->parser.std_in = readline(data->prompt);
	if (!data->parser.std_in)
		clean_display(data);
	if (ft_strcmp(data->parser.std_in, "") != 0)
		add_history(data->parser.std_in);
	if (is_empty(data->parser.std_in) == 1)
	{
		ft_free(data->parser.std_in);
		display_prompt(data);
		return ;
	}
	splitter(data);
	ft_free(data->parser.std_in);
	if (data->status != 1)
	{
		data->status = 1;
		free_tab(data->parser.parsed);
		get_exit_stat(1);
		display_prompt(data);
		return ;
	}
}
