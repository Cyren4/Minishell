/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/10 12:42:05 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_prompt(t_gen *data)
{
	// ft_putstr_fd("minishell $ ", 1);
	data->std_in = readline("minishell $ ");
	printf("Line read: %s\n", data->std_in);
	data->show_prompt = 0;
}