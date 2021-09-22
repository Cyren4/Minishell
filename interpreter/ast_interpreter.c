/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:20:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 10:34:20 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interprete.h"


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

t_tree *build_pipe(t_tree *ast, t_lexer *lex, t_lexer *head)
{
	t_tree *new;

	if (head == lex)
		return (NULL);
	new = malloc(sizeof(t_tree));
	if (!new)
		return (0);
	new->type = PIPE;
	ast = new;
	ast->right = build_tree(lex->next);
	cut_lexer(head, lex);
	ast->left = build_tree(head);
	return (ast);
}

t_tree *build_leaf(t_lexer *lexer)
{
	t_tree *leaf;

	leaf = malloc(sizeof(t_tree));
	if (!leaf)
		return (NULL);
	leaf->type = CMD;
	leaf->cmd = lexer;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}

t_tree *build_tree(t_lexer *lexer)
{
	t_tree *ast;
	t_lexer *curr_lex;
	
	curr_lex = lexer;
	while (curr_lex && curr_lex->token != PIPE)
		curr_lex = curr_lex->next;
	if (curr_lex && curr_lex->token == PIPE)
		ast = build_pipe(ast, curr_lex, lexer);
	else
		ast = build_leaf(lexer);
	return ast;
	
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
	// lexer = add_custom_elem_to_lexer(lexer, "echo", WORD);
	// lexer = add_custom_elem_to_lexer(lexer, "hello", WORD);
	// lexer = add_custom_elem_to_lexer(lexer, ">", GT);
	// lexer = add_custom_elem_to_lexer(lexer, "file", WORD);
	lexer = add_custom_elem_to_lexer(lexer, "|", PIPE);
	lexer = add_custom_elem_to_lexer(lexer, "ls", WORD);
	// lexer = add_custom_elem_to_lexer(lexer, "|", PIPE);
	// lexer = add_custom_elem_to_lexer(lexer, "ls2", WORD);
	// add_custom_elem_to_lexer(lexer, "echo", WORD);
	ast = NULL;
	ast = build_tree(lexer);
	if (ast == NULL)
		printf("Error! bad input\n");
	return (0);
}