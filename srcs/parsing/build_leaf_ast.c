/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_leaf_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:05:01 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/30 14:48:47 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redir(t_tree *leaf, t_lexer *lexer)
{
	t_lexer	*new;
	t_lexer	*head;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	new = lexer;
	new->next->next = NULL;
	if (!leaf->redir)
		leaf->redir = new;
	else
	{
		head = leaf->redir;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_tree	*build_leaf(t_lexer *lexer)
{
	t_tree	*leaf;
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*old_head;

	leaf = malloc(sizeof(t_tree));
	if (!leaf || !lexer)
		return (NULL);
	// create_double_list(lexer);
	leaf->type = CMD;
	leaf->cmd = lexer;
	leaf->redir = NULL;
	leaf->fd_in = STDIN_FILENO;
	leaf->fd_out = STDOUT_FILENO;
	leaf->left = NULL;
	leaf->right = NULL;
	head = leaf->cmd;
	while (head && head->next)
	{
		if (head && head->token >= LT && head->token <= GT2)
		{
			tmp = head->next->next;
			add_redir(leaf, head);
			head = old_head;
			head->next = tmp;
		}
		old_head = head;
		head = head->next;
	}
	return (leaf);
}
