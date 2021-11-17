/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 07:33:17 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 20:30:05 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_gen	*get_data(t_gen *data)
{
	static t_gen	*cur_data = NULL;

	if (data != NULL)
		cur_data = data;
	return (cur_data);
}

int	get_pid(int pid)
{
	static int	cur_pid = 0;

	if (pid != -1)
		cur_pid = pid;
	return (cur_pid);
}

int	get_exit_stat(int stat)
{
	static int	cur_stat = 0;

	if (stat != -1)
		cur_stat = stat;
	return (cur_stat);
}