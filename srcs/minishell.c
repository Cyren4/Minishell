/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/26 17:11:01 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	get_status(int exit_stat, int write)
{
	if (WIFEXITED(exit_stat))
		get_exit_stat(WEXITSTATUS(exit_stat));
	if (WIFSIGNALED(exit_stat))
	{
		get_exit_stat(WTERMSIG(exit_stat) + 128);
		if (get_exit_stat(-1) == 130)
			printf("\n");
		else if (get_exit_stat(-1) == 131 && write)
			printf("Quit (core dumped)\n");
	}
}

void	execution(t_gen *data)
{
	int	total_cmds;
	int	i;

	total_cmds = 0;
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
			while (data->pids[0] != -1 && ++i < total_cmds)
			{
				waitpid(data->pids[i], &data->exit_stat, 0);
				get_status(data->exit_stat, i + 1 == total_cmds);
			}
			close_pipes(data->ast);
		}
	}
}

int	minishell_loop(t_gen *data)
{
	while (data->status != 0)
	{
		receive_sig();
		display_prompt(data);
		create_paths(data);
		data->lex = lexer(data->parser.parsed, data);
		if (data->status == -1)
		{
			clean_lex(data->lex);
			clean_data(data);
			continue ;
		}
		data->ast = build_tree1(data->lex);
		execution(data);
		clean_data(data);
	}
	return (get_exit_stat(-1));
}

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
	ret = minishell_loop(&data);
	delete_data(&data);
	return (ret);
}
