/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:28:23 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/30 17:00:25 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	create_pipes(t_tree *ast)
{
	t_tree	*head;
	int		fd[2];

	head = ast;
	if (head->type == PIPE)
	{
		if (!ast->left || !ast->right)
			return (0);
		if (pipe(fd) < 0)
			return (0);
		ast->left->fd_in = ast->fd_in;
		ast->left->fd_out = fd[1];
		ast->right->fd_in = fd[0];
	}
	if (head->left)
		create_pipes(head->left);
	if (head->right)
		create_pipes(head->right);
	return (1);
}
