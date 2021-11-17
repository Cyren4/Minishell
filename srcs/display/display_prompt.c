/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/17 20:46:53 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_display(t_gen *data)
{
	ft_free(data->home);
	// ft_free(data->prompt);
	// clean_env(data);
	clear_history();
}

void	display_prompt(t_gen *data)
{
	get_pid(1);
	data->parser.std_in = readline(data->prompt);
	if (!data->parser.std_in)
	{
		printf("\b\b  \b\bexit\n");
		clean_display(data);
		exit(get_exit_stat(-1));
	}
	if (ft_strcmp(data->parser.std_in, "") != 0)
		add_history(data->parser.std_in);
	if (is_empty(data->parser.std_in) == 1)
	{
		ft_free(data->parser.std_in);
		display_prompt(data);
	}
	splitter(data);
	if (data->status != 1)
	{
		data->status = 1;
		ft_free(data->parser.std_in);
		free_tab(data->parser.parsed);
		exit(get_exit_stat(1));
		display_prompt(data);
	}
}
