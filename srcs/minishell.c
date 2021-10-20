/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/20 17:31:00 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_data(t_gen *data)
{
	// receiveSIG();
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
	if (data->lex != NULL)
		clean_lex(data->lex);
	data->lex = NULL;
	clean_parser(&data->parser);
	// data->parser.std_in = NULL;
	// data->parser.parsed = NULL;
}

void delete_data(t_gen *data)
{
	// clean_lex(data->lex);
	// data->lex = NULL;
	// clean_parser(&data->parser);
	clean_env(data->env);
	if (data->prompt != NULL)
		free(data->prompt);
	// clear_history();
}

int no_pipe(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int minishell_loop(t_gen *data)
{
	int total_cmds;

	// clean_data(data);
	while (data->status == 1)
	{
		// receiveSIG();
		display_prompt(data);
		data->lex = lexer(data->parser.parsed, data);
		if (ft_strcmp(data->lex->content, "exit") == 0 && no_pipe(data->lex))
			if (ft_exit(data, data->lex->next)== 1)
				continue;
		data->ast = build_tree1(data->lex);
		if (!data->ast)
			error(data, BAD_INPUT);
		else
		{
			// structure(data->ast, 0);
			create_pipes(data->ast);
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
	return (data->exit_stat);
}

int main(int ac, char **av, char **env)
{
	t_gen data;
	int ret;

	(void)av;
	ret = 0;
	if (ac == 100)
		return (0);
	init_data(&data);
	stock_env_vars(&data, env);
	get_data(&data);
	ret = minishell_loop(&data);
	delete_data(&data);
	return (ret);
}