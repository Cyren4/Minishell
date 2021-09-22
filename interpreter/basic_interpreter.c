/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:58:20 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 18:01:44 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interprete.h"

void create_node(t_gen *data, char *content, int token)
{
	t_lexer *new;
	t_lexer *head;

	
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->content = content;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	if (!data->lex)
		data->lex = new;
	else
	{
		head = data->lex;
		while (data->lex->next)
			data->lex = data->lex->next;
			new->prev = data->lex;
		data->lex->next = new;
		data->lex = head;
	}

}

void error(int e)
{
	if (e == 1)
		printf("Incorrect Syntax\n");
	if (e == 2)
		printf("Incorrect Syntax2\n");
	exit(1);
}

void check_tokens(t_gen *data)
{
	t_lexer *head;


	head = data->lex;
	while (data->lex)
	{
		if (data->lex->token == PLUS || data->lex->token == MINUS)
		{
			if (data->lex->prev->token != INT || data->lex->next->token != INT)
				error(1);
		}
		data->lex = data->lex->next;
	}
	data->lex = head;
}

void create_lexer(t_gen *data, char *str)
{
	t_lexer *new;
	int i;
	int start;
	char *content;

	i = 0;
	start = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-' && str[i] != ' ')
			error(1);
		if (str[i] == '+')
			create_node(data, "+", PLUS);
		if (str[i] == '-')
			create_node(data, "-", MINUS);
		if (str[i] >= '0' && str[i] <= '9')
		{
			start = i;
			while (str[i] >= '0' && str[i] <= '9')
				i++;
			content = ft_substr(str, start, i - start); 
			create_node(data, content, INT);
		}
		else
			i++;
	}
	check_tokens(data);
}

void do_operations(t_gen *data)
{
	int result;
	t_lexer *head;
	
	result = ft_atoi(data->lex->content);
	head = data->lex;
	while (data->lex)
	{
		if (data->lex->token == PLUS)
			result = atoi(data->lex->prev->content) + atoi(data->lex->next->content);
		else if (data->lex->token == MINUS)
			result = atoi(data->lex->prev->content) - atoi(data->lex->next->content);
		data->lex = data->lex->next;
	}
	printf("Result = %d\n", result);
	data->lex = head;
}

void do_operation(t_lexer *lex, int direc)
{
	t_lexer *dir;
	int result;

	if (direc == RIGHT)
		dir = lex->next;
	else if (direc == LEFT)
		dir = lex->prev;
	while (dir)
	{
		if (dir->token == PLUS)
			result = do_operation(data)
	}
}

int main(int ac, char **av)
{
	int i;
	char *std_in;
	t_gen data;

	if (ac != 2)
		error(1);
	create_lexer(&data, av[1]);
	do_operations(&data);
	return 0;
}