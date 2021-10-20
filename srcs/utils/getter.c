/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 07:33:17 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/19 17:55:53 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_gen   *get_data(t_gen *data)
{
	static t_gen *cur_data = NULL;

	if (data != NULL)
		cur_data = data;
	return (cur_data);
}
