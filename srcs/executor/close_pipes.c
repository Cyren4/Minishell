/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:54:06 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/16 15:35:43 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int close_pipes(t_tree *ast)
{
    t_tree	*head;

	head = ast;
	if (ast->fd_in != 0)
		close(ast->fd_in);
	if (ast->fd_out != 1)
		close(ast->fd_out);
	if (head->left)
		close_pipes(head->left);
	if (head->right)
		close_pipes(head->right);
	return (1);
	}
