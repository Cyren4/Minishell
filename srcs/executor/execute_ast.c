/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:09:02 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/07 11:09:51 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_ast(t_gen *data, t_tree *ast)
{
	t_tree *head;

	head = ast;
	if (head->type == CMD)
		return (execute_command(data, head));
	if (head->left)
		 return (execute_ast(data, head->left));
	if (head->right)
		return (execute_ast(data, head->right));
	return (1);
}