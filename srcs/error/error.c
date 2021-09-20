/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:35 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/20 16:48:17 by vbaron           ###   ########.fr       */
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
			free(data->parser.parsed[i]);
	}
	exit (1);
}

void error(t_gen *data, int e)
{
	if (e == QUOTES_UNCLOSED)
		printf("Error\n- Quotes unclosed -\n");
	if (e == BAD_MALLOC)
		printf("Error\n- Bad Malloc -\n");
	ft_clean(data);
}