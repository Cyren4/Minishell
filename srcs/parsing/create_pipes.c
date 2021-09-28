/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:28:23 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/28 13:58:42 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int create_pipes(t_tree *ast)
{
	t_tree *head = ast;
	int fd[2];

	if (head->type == PIPE)
	{
		if (pipe(fd) < 0)
			return (0);
		else
		{
			head->left->std_in = head->std_in;
			head->left->std_out = fd[1];
			head->right->std_in = fd[0];
		}
	}
	if (head->left)
		create_pipes(head->left);
	else if (head->right)
		create_pipes(head->right);
	return (1);
}