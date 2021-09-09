/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/09 18:07:48 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	set_data(t_data *data)
{
	data->status = 1;
	data->line = NULL;

}

int main(int ac, char **av, char **env)
{
	t_data	data;
	int			status;

	if (ac != 1)
		error(av[0]);
	set_data(&data);
	while (data.status)
	{
		display_prompt(data);
	}
	return(0);
}