/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 07:33:17 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/14 17:24:41 by cramdani         ###   ########.fr       */
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

// t_pid	*get_pid(t_gen *data)
// {
// 	static t_gen	*cur_data = NULL;

// 	if (data != NULL)
// 		cur_data = data;
// 	return (cur_data);
// }
