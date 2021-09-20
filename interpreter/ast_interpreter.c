/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:20:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/20 16:26:56 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interprete.h"


// Syntax grammar

// pipe_sequence : basic_command					 pipe_sequence1
// 	 		  | pipe_sequence | basic_command        pipe_sequence2

// basic_command : built_in							 basic_command1
// 			  | built_in  args                       basic_command2

// args : word										  args_1
// 	 | word word									  args_2	

// word : WORD;                                        word_node

void *word_node(t_lexer *p)
{
	t_word *w;

	w = NULL;

	if (p->token ==  WORD)
	{
		w = malloc(sizeof(t_word));
		w->data = ft_strdup(p->content);
		p = p->next;
		return (w);
	}
	else
		return (NULL);
	
}

void pipe_sequence(t_tree *ast, t_lexer *lexer)
{

}

void build_tree(t_tree *ast, t_lexer *lexer)
{
	while (lexer->token != PIPE)
		lexer = lexer->next
	
	if (lexer->token == PIPE)
		build_parent(ast, lexer);
}

int main()
{
	t_tree *ast;
	t_lexer *lexer;

	ast->head = lexer;
	ast->curr_pos = lexer;	
	build_tree(ast, lexer);
}