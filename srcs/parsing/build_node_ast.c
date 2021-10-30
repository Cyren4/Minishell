/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_node_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:03:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/30 14:48:05 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cut_lexer(t_lexer *head, t_lexer *lex)
{
	t_lexer	*head2;

	head2 = head;
	while (head->next != lex)
		head = head->next;
	head->next->content = NULL;
	head->next = NULL;
	head = head2;
}

t_tree	*build_node(t_lexer *lex, t_lexer *head, int type)
{
	t_tree	*new;

	if (lex == head || !lex->next)
		return (NULL);
	new = malloc(sizeof(t_tree));
	if (!new)
		return (0);
	new->type = type;
	new->cmd = NULL;
	new->redir = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->right = build_tree1(lex->next);
	cut_lexer(head, lex);
	ft_free(lex);
	new->left = build_tree1(head);
	return (new);
}
