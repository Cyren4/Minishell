/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:35 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/28 15:52:56 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	arg_error(char *exec)
{
	printf("Error : Expect 0 arguments\n");
	printf("Usage : %s\n", exec);
	exit(0);
}

void	error(t_gen *data, int e)
{
	if (data->status == -1)
		return ;
	get_exit_stat(1);
	if (e == QUOTES_UNCLOSED)
		print_error("Error\n- Quotes unclosed -\n", NULL, NULL);
	if (e == BAD_MALLOC)
		print_error("Error\n- Bad Malloc -\n", NULL, NULL);
	if (e == BAD_INPUT)
		print_error("Error\n- Bad Input -\n", NULL, NULL);
	if (e == -1)
	{
		ft_putstr_fd(data->str_err, data->std_out);
		get_exit_stat(127);
	}
	data->status = -1;
}

void	print_error(char *m1, char *cmd, char *m2)
{
	if (m1)
		ft_putstr_fd(m1, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (m2)
		ft_putstr_fd(m2, 2);
}
