/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe_node_ast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:03:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 18:05:06 by vbaron           ###   ########.fr       */
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

t_tree *build_pipe(t_lexer *lex, t_lexer *head)
{
	t_tree *new;

	if (head == lex)
		return (NULL);
	new = malloc(sizeof(t_tree));
	if (!new)
		return (0);
	new->type = PIPE;
	new->right = build_tree(lex->next);
	cut_lexer(head, lex);
	new->left = build_tree(head);
	return (new);
}