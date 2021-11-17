/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 20:17:50 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_gen *data)
{
	data->prompt = ft_strdup("minishell $ ");
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->env = NULL;
	data->lex = NULL;
	data->hdoc = 0;
	data->status = 1;
	data->exit_stat = 0;
	data->home = NULL;
	data->paths = NULL;
	data->ast = NULL;
	data->str_err = NULL;
	data->pids = NULL;
	get_pid(0);
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

void	get_status(t_gen *data)
{
	if (WEXITSTATUS(data->exit_stat))
	{
		data->exit_stat = WEXITSTATUS(data->exit_stat);
		get_exit_stat(data->exit_stat);
	}
	// if (WIFSIGNALED(data->exit_stat))
	// {
	// 	data->exit_stat = WTERMSIG(data->exit_stat);
	// 	if (data->exit_stat != 131)
	// 		data->exit_stat += 128;
	// }
}

int	minishell_loop(t_gen *data)
{
	int	total_cmds;
	int	i;

	total_cmds = 0;
	receiveSIG();
	while (data->status != 0)
	{
		display_prompt(data);
		create_paths(data);
		data->lex = lexer(data->parser.parsed, data);
		if (data->status == -1)
		{
			clean_data(data);
			continue ;
		}
		// data->status = 0;
		// data->lex = lexer(data->av, data);
		// /*
		data->ast = build_tree1(data->lex);
		if (!data->ast)
			error(data, BAD_INPUT);
		else
		{
			if (create_pipes(data->ast))
			{
				total_cmds = calculate_commands(data->ast);
				data->tracker = 0;
				data->pids = malloc(sizeof(pid_t) * total_cmds);
				initialise_pids(data, total_cmds);
				if (!execute_ast(data, data->ast, 0))
					error(data, -1);
				i = -1;
				while (++i < total_cmds)
				{
					waitpid(data->pids[i], &data->exit_stat, 0);
					get_status(data);
					// print_error(data->exit_stat);
				}
				close_pipes(data->ast);
			}
		}
		clean_data(data);
	}
	return (get_exit_stat(-1));
}
// int return_value = WEXITSTATUS(data->exit_stat);
// printf("return value: %d\n", return_value);
// printf("pids[%d]:%d", i, data->pids[i]);

int	main(int ac, char **av, char **env)
{
	t_gen	data;
	int		ret;

	ret = 0;
	if (ac != 1)
	{
		printf("Error\nUsage: %s\n", av[0]);
		return (1);
	}
	init_data(&data);
	stock_env_vars(&data, env);
	get_data(&data);
	// data.av = &av[1];
	receiveSIG();
	ret = minishell_loop(&data);
	delete_data(&data);
	// clean_lexlete_data(&data);
	return (ret);
}
