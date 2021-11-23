/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_pids.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:36:52 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/23 23:23:54 by cramdani         ###   ########.fr       */
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
