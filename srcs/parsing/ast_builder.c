/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:02:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/23 16:00:23 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree *build_tree2(t_lexer *lexer)
{
	t_tree *ast;
	t_lexer *curr_lex;
	
	curr_lex = lexer;
	while (curr_lex && !(curr_lex->token >= LT && curr_lex->token <= GT2))
		curr_lex = curr_lex->next;
	if (curr_lex)
		ast = build_node(curr_lex, lexer, curr_lex->token);
	else
		ast = build_leaf(lexer);
	return (ast);
}

t_tree *build_tree1(t_lexer *lexer)
{
	t_tree *ast;
	t_lexer *curr_lex;
	
	curr_lex = lexer;
	while (curr_lex && curr_lex->token != PIPE)
		curr_lex = curr_lex->next;
	if (curr_lex)
		ast = build_node(curr_lex, lexer, curr_lex->token);
	else
		ast = build_tree2(lexer);
	return ast;
}