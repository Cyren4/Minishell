/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_leaf_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:05:01 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/16 19:24:39 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_redir(t_tree *leaf, t_lexer *lexer)
{
	t_lexer	*new;
	t_lexer	*head;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	new = lexer;
	if (new->next)
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

void	add_cmd(t_tree *leaf, t_lexer *lexer)
{
	t_lexer	*new;
	t_lexer	*head;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	new = lexer;
	if (new->next)
		new->next = NULL;
	if (!leaf->cmd)
		leaf->cmd = new;
	else
	{
		head = leaf->cmd;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_tree	*build_leaf(t_lexer *lexer)
{
	t_tree	*leaf;
	t_lexer	*head;
	t_lexer *tmp;

	leaf = malloc(sizeof(t_tree));
	if (!leaf || !lexer)
		return (NULL);
	leaf->type = CMD;
	leaf->cmd = NULL;
	leaf->redir = NULL;
	leaf->fd_in = STDIN_FILENO;
	leaf->fd_out = STDOUT_FILENO;
	leaf->left = NULL;
	leaf->right = NULL;
	head = lexer;
	while (head)
	{
		if (head && head->next && head->token >= LT && head->token <= GT2)
		{
			tmp = head->next->next;
			add_redir(leaf, head);
			head = tmp;
		}
		else
		{
			tmp = head->next;
			add_cmd(leaf, head);
			head = tmp;
		}
		
	}
	return (leaf);
}
