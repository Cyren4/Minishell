/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:02:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/11 18:20:33 by vincentbaro      ###   ########.fr       */
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
	
	if (lexer == NULL)
		return (0);
	curr_lex = lexer;
	while (curr_lex && curr_lex->token != PIPE)
		curr_lex = curr_lex->next;
	if (curr_lex)
		ast = build_node(curr_lex, lexer, curr_lex->token);
	else
		ast = build_leaf(lexer);
	return ast;
}