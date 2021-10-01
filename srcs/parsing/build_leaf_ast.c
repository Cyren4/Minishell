/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_leaf_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:05:01 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/01 15:23:51 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree *build_leaf(t_lexer *lexer)
{
	t_tree *leaf;

	leaf = malloc(sizeof(t_tree));
	if (!leaf || !lexer)
		return (NULL);
	leaf->type = CMD;
	leaf->cmd = lexer;
	leaf->fd_in = STDIN_FILENO;
	leaf->fd_out = STDOUT_FILENO;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}