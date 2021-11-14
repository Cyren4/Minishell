/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@stuclean_lexnt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/12 15:19:44 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_gen *data)
{
	data->env = NULL;
	data->hdoc = 0;
	data->lex = NULL;
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->status = 1;
	data->exit_stat = 0;
	data->ast = NULL;
	data->prompt = ft_strdup("minishell $ ");
	data->str_err = NULL;
}

int	no_pipe(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

		// if (ft_strcmp(data->lex->content, "exit") == 0 && no_pipe(data->lex))
		// 	if (ft_exit(data, data->lex->next)== 1)
		// 		continue
int	minishell_loop(t_gen *data)
{
	int	total_cmds;
	int	i;

	total_cmds = 0;
	receiveSIG();
	while (data->status != 0)
	{
		create_paths(data);
		display_prompt(data);
		data->lex = lexer(data->parser.parsed, data);
		if (data->status == -1)
		{
			clean_data(data);
			continue ;
		}
		// display_token(data->lex);
		// data->status = 0;
		// data->lex = lexer(data->av, data);
		// /*
		data->ast = build_tree1(data->lex);
		if (!data->ast)
			error(data, BAD_INPUT);
		else
		{
			// structure(data->ast, 0);
			if (create_pipes(data->ast))
			{
				total_cmds = calculate_commands(data->ast);
				data->tracker = 0;
				data->pids = malloc(sizeof(pid_t) * total_cmds);
				if (!execute_ast(data, data->ast, 0))
					error(data, -1);
				i = -1;
				while (++i < total_cmds)
				{
					waitpid(data->pids[i], &data->exit_stat, 0);
					// print_error(data->exit_stat);
				}
			}
		}
		clean_data(data);
		// */
	}
	return (data->exit_stat);
}
					// int return_value = WEXITSTATUS(data->exit_stat);
					// printf("return value: %d\n", return_value);
					// printf("pids[%d]:%d", i, data->pids[i]);

int	main(int ac, char **av, char **env)
{
	t_gen	data;
	int		ret;

	(void)av;
	(void)ac;
	ret = 0;
	// if (ac != 1)
	// 	return (-1);
	init_data(&data);
	stock_env_vars(&data, env);
	get_data(&data);
	data.av = &av[1];
	receiveSIG();
	ret = minishell_loop(&data);
	// clean_lexlete_data(&data);
	return (ret);
}
