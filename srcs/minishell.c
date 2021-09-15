/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/15 17:47:51 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	set_data(t_gen *data)
{
	data->status = 1;
}

int main(int ac, char **av, char **env)
{
	t_gen	data;

	(void)av;
	(void)env;
	if (ac != 1)
		return (0);
	set_data(&data);
	while (data.status)
	{
		display_prompt(&data);
	}
	return(0);
}