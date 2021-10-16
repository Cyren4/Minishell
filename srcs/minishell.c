/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/16 06:55:54 by cramdani         ###   ########.fr       */
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

int		maj_sig(int sig)
{
	static int	cur_sig = -1;

	if (sig != -1)
		cur_sig = sig;
	return (cur_sig);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	maj_sig(sig);
}

void	receiveSIG(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int prompt(t_gen *data)
{
	int total_cmds;
	
	while (data->status)
	{
		
		display_prompt(data);
		data->lex = lexer(data->parser.parsed, data);
		// data.lex = lexer(&av[1], &data);
		// display_token(data->lex);
		// if (data->lex->is_builtin == 1)
		// 	data->exit_stat = exec_builtin(data, data->lex);
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
		clean_data(data);
	}
	return (data->exit_stat);
}

int main(int ac, char **av, char **env)
{
	t_gen	data;
	int		ret;

	(void)av;
	if (ac == 100)
		return (0);
	init_data(&data);
	stock_env_vars(&data, env);
	ret = prompt(&data);
	delete_data(&data);
	return (ret);
}