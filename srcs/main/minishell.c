/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/10 15:29:05 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

void	set_data(t_gen *data)
{
	data->show_prompt = 1;
	data->status = 1;
}

int main(int ac, char **av)
{
	t_gen	data;

	(void)av;
	if (ac != 1)
		return (0);
	set_data(&data);
	while (data.status)
	{
		if (data.show_prompt == 1)
			display_prompt(&data);
	}
	return(0);
}