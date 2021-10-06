/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:28:23 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/06 21:06:28 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int create_pipes(t_tree *ast)
{
	t_tree *head;
	int fd[2];

	head = ast;
	if (head->type == PIPE)
	{
		if (pipe(fd) < 0)
			return (0);
		if (dup2(head->fd_in, head->left->fd_in) == -1)
			return (0);
		if (dup2(head->left->fd_out, fd[1]) == -1)
			return (0);
		if (close(fd[1]) == -1)
			return (0);
		if (dup2(fd[0], head->right->fd_in) == -1)
			return(0);
		if (close(fd[0]) == -1)
			return (0);
	}
	if (head->left)
		return (create_pipes(head->left));
	if (head->right)
		return (create_pipes(head->right));
	return (1);
}