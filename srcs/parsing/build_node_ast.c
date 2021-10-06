/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_node_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:03:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/06 21:01:19 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void cut_lexer(t_lexer *head, t_lexer *lex)
{
	t_lexer *head2;
	
	head2 = head;
	while (head->next != lex)
		head = head->next;
	head->next->content = NULL;
	head->next = NULL;
	head = head2;
}
t_tree *build_node(t_lexer *lex, t_lexer *head, int type)
{
	t_tree *new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (0);
	new->type = type;
	new->cmd = NULL;
	new->redir = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = NULL;
	new->right = build_tree1(lex->next);
	cut_lexer(head, lex);
	new->left = build_tree1(head);
	return (new);
}