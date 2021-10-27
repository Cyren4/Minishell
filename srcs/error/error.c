/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:35 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/27 15:27:27 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	arg_error(char  *exec)
{
	printf("Error : Expect 0 arguments\n");
	printf("Usage : %s\n", exec);
	exit(0);
}

void ft_clean(t_gen *data)
{
	int i;
	if (data->parser.std_in)
		free(data->parser.std_in);
	if (data->parser.parsed)
	{
		i = -1;
		while (data->parser.parsed[++i])
		{
			if (data->parser.parsed[i])
				ft_free(data->parser.parsed[i]);
		}
	}
}

void error(t_gen *data, int e)
{
	(void)data;
	if (e == QUOTES_UNCLOSED)
		printf("Error\n- Quotes unclosed -\n");
	if (e == BAD_MALLOC)
		printf("Error\n- Bad Malloc -\n");
	if (e == BAD_INPUT)
		printf("Error\n- Bad Input -\n");
	if (e == -1)
		ft_putstr_fd(data->str_err, data->std_out);
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