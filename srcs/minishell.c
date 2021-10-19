/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/18 16:21:18 by vbaron           ###   ########.fr       */
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
	data->prompt = ft_strdup("minishell $ ");
	data->str_err = NULL;
}

void clean_data(t_gen *data)
{
	clean_lex(data);
	clean_parser(&data->parser);
	clean_tree(data->ast);
	// data->parser.std_in = NULL;
	// data->parser.parsed = NULL;
}

void delete_data(t_gen *data)
{
	clean_lex(data);
	data->lex = NULL;
	clean_parser(&data->parser);
	clean_env(data);
	if (data->prompt != NULL)
		ft_free(data->prompt);
	// clear_history();
}

int prompt(t_gen *data, char **args)
{
	int total_cmds;
	(void)args;

	total_cmds = 0;
	while (data->status)
	{
		data->status = 0;
		// display_prompt(data);
		// data->lex = lexer(data->parser.parsed, data);
		data->lex = lexer(args, data);
		// display_token(data->lex);
		data->ast = build_tree1(data->lex);
		if (!data->ast)
			error(data, BAD_INPUT);
		else
		{
			// structure(data->ast, 0);
			if (create_pipes(data->ast))
			{
				total_cmds = calculate_commands(data->ast);
				if (!execute_ast(data, data->ast))
					error(data, -1);
				while (total_cmds >= 0)
				{
					wait(NULL);
					total_cmds--;
				}
			}
		}
		clean_data(data);
	}
	return (EXIT_SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_gen data;
	int ret;

	(void)av;
	if (ac == 100)
		return (0);
	init_data(&data);
	stock_env_vars(&data, env);
	ret = prompt(&data, &av[1]);
	delete_data(&data);
	return (ret);
}