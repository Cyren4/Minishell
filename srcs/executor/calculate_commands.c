/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:14:31 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/07 17:33:46 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int calculate_commands(t_tree *ast)
{
	t_tree *head;
	int total;

	head = ast;
	total = 0;
	if (head->type == CMD)
		return (1);
	if (head->left)
		total += calculate_commands(head->left);
	if (head->right)
		total += calculate_commands(head->right);
	return (total);
}