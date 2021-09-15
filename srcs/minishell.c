/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/15 19:14:59 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	init_data(t_gen *data)
{
	data->env = NULL;
	data->lex = NULL;
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
}

int main(int ac, char **av, char **env)
{
	t_gen	data;

	(void)av;
	if (ac != 1)
		return (0);
	init_data(&data);
	stock_env_vars(&data, env);
	// while (data.status)
	// {
	// 	display_prompt(&data);
	// }
	return(0);
}