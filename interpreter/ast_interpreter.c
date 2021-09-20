/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:20:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/20 18:52:46 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interprete.h"


void cut_lexer(t_lexer *lex)
{
	free(lex->content);
	lex = NULL;
}

int build_pipe(t_tree *ast, t_lexer *lex, t_lexer *head)
{
	t_tree *new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (0);
	new->type = PIPE;
	ast = new;
	build_tree(ast->right, lex->next);
	cut_lexer(lex);
	build_tree(ast->left, head);
	return (0);
}

int build_tree(t_tree *ast, t_lexer *lexer)
{
	t_lexer *curr_lex;
	t_tree *curr_ast;
	
	curr_lex = lexer;
	curr_ast = ast;
	while (curr_lex->token != PIPE)
		curr_lex = curr_lex->next;
	if (curr_lex->token == PIPE)
		build_pipe(curr_ast, curr_lex, lexer);
	return (0);
	
}

t_lexer *add_custom_elem_to_lexer(t_lexer *lexer, char *content, int token)
{
	t_lexer *new;
	t_lexer *head;

	head = lexer;
	new = malloc(sizeof(t_lexer));
	new->content = content;
	new->token = token;
	new->next = NULL;
	if (!lexer)
		lexer = new;
	else
	{
		while (lexer->next != NULL)
			lexer = lexer->next;
		lexer->next = new;
		lexer = head;
	}
	return (lexer);
}

int main()
{
	t_tree *ast;
	t_lexer *lexer;

	lexer = NULL;
	lexer = add_custom_elem_to_lexer(lexer, "echo", WORD);
	lexer = add_custom_elem_to_lexer(lexer, "hello", WORD);
	lexer = add_custom_elem_to_lexer(lexer, "|", PIPE);
	lexer = add_custom_elem_to_lexer(lexer, "ls", WORD);
	// add_custom_elem_to_lexer(lexer, "echo", WORD);
	ast = NULL;
	build_tree(ast, lexer);
}