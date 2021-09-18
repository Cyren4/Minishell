/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:58:20 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/18 19:39:06 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interprete.h"

void create_node(t_lexer *lex, char *content, int token)
{
	t_lexer *new;
	t_lexer *head;

	head = lex;
	new->content = content;
	new->token = token;
	if (!lex)
		lex = new;
	else
	{
		while (lex->next)
			lex = lex->next;
		lex->next = new;
	}
	lex = head;

}

void error(int e)
{
	if (e == 1)
		printf("Incorrect Syntax\n");
	if (e == 2)
		printf("Incorrect Syntax2\n");
	exit(1);
}

void check_tokens(t_lexer *lex)
{
	t_lexer *head;

	head = lex;
	while (lex->next->next)
	{
		if ((lex->next->token != PLUS || lex->token != MINUS) || lex->token != INT)
			error(2);
		lex = lex->next->next;
	}
	lex = head;
}

void create_lexer(t_lexer *lex, char *str)
{
	t_lexer *new;
	int i;
	int start;
	char *content;

	i = 0;
	start = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') || str[i] != '+' || str[i] != '-' || str[i] != ' ')
			error(1);
		if (str[i] == '+')
			create_node(lex, "+", PLUS);
		if (str[i] == '-')
			create_node(lex, "-", MINUS);
		if (str[i] >= '0' || str[i] <= '9')
		{
			start = i;
			while (str[i] >= '0' || str[i] <= '9')
				i++;
			content = ft_substr(str, start, i - start); 
			create_node(lex, content, INT);
		}
		else
			i++;
	}
	check_tokens(lex);
}

void do_operations(t_lexer *lex)
{
	int result;
	t_lexer *head;
	
	result = ft_atoi(lex->content);
	while (lex->next->next != NULL)
	{
		if (lex->next->token == MINUS)
			result = result - ft_atoi(lex->next->next->content);
		if (lex->next->token == PLUS)
			result = result + ft_atoi(lex->next->next->content);
		lex = lex->next->next;
	}
	printf("Result = %d\n", result);
	lex = head;
}

int main(int ac, char **av)
{
	int i;
	char *std_in;
	t_lexer *lex;

	
	while (1)
	{
		lex = NULL;
		i = 0;
		// std_in = readline("Vinny's Interpreter => ");
		create_lexer(lex, av[1]);
		do_operations(lex);
	}
	return 0;
}