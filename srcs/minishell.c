/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/04 16:53:00 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_data(t_gen *data)
{
	data->env = NULL;
	data->lex = NULL;
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->status = 1;
	data->exit_stat = 0;
	data->ast = NULL;
	data->str_err = NULL;
	dup2(STDIN_FILENO, data->std_in);
	dup2(STDOUT_FILENO, data->std_out);
	dup2(STDERR_FILENO, data->std_err);
}

void clean_lex(t_lexer *lex)
{
	t_lexer *cur;
	t_lexer *next;

	if (lex == NULL)
		return;
	cur = lex;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void clean_parser(t_pars *pars)
{
	int i;

	i = 0;
	if (pars == NULL)
		return;
	if (pars->parsed)
	{
		while (pars->parsed[i])
		{
			if (pars->parsed[i])
				free(pars->parsed[i]);
			i++;
		}
	}
	free(pars->parsed);
	if (pars->std_in)
		free(pars->std_in);
}

void clean_data(t_gen *data)
{
	clean_lex(data->lex);
	data->lex = NULL;
	clean_parser(&data->parser);
	// data->parser.std_in = NULL;
	// data->parser.parsed = NULL;
}

int main(int ac, char **av, char **env)
{
	t_gen data;

	// if (ac != 1)
	// 	return (0);
	(void)ac;
	(void)av;
	init_data(&data);
	stock_env_vars(&data, env);
	while (data.status)
	{
		data.status = 0;
		// display_prompt(&data);
		// data.lex = lexer(data.parser.parsed, &data);
		data.lex = lexer(&av[1], &data);
		display_token(data.lex);
		data.ast = build_tree1(data.lex);
		if (!data.ast)
			error(&data, BAD_INPUT);
		else
		{
			structure(data.ast, 0);
			create_pipes(data.ast);
			if (!execute_ast(&data, data.ast))
				error(&data, -1);
		}
		clean_data(&data);
	}
	// clear_history();
	// rl_clear_history(); // sur linux
	return (0);
}