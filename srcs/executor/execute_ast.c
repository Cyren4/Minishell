/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:09:02 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/24 11:31:01 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_ast(t_gen *data, t_tree *ast, int pipe)
{
	t_tree	*head;

	head = ast;
	if (head->type == PIPE)
		pipe = 1;
	if (head->type == CMD)
		execute_command(data, head, pipe);
	if (head->left)
		execute_ast(data, head->left, pipe);
	if (head->right)
		execute_ast(data, head->right, pipe);
	return (1);
}
