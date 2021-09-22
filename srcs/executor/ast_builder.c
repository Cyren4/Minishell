/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:02:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 18:05:37 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree *build_tree(t_lexer *lexer)
{
	t_tree *ast;
	t_lexer *curr_lex;
	
	curr_lex = lexer;
	while (curr_lex && curr_lex->token != PIPE)
		curr_lex = curr_lex->next;
	if (curr_lex && curr_lex->token == PIPE)
		ast = build_pipe(curr_lex, lexer);
	else
		ast = build_leaf(lexer);
	return ast;
	
}