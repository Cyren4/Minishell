/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/20 18:06:05 by cramdani         ###   ########.fr       */
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
	clean_tree(data->ast);
}

void delete_data(t_gen *data)
{
	data->lex = NULL;
	clean_env(data);
	// if (data->paths)
	// 	ft_free(data->paths);
	if (data->prompt != NULL)
		ft_free(data->prompt);
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
	int i;

	// clean_data(data);
	total_cmds = 0;
	while (data->status == 1)
	{
		// receiveSIG();
		// data->status = 0;
		display_prompt(data);
		data->lex = lexer(data->parser.parsed, data);
		// data->lex = lexer(data->av, data);
		if (ft_strcmp(data->lex->content, "exit") == 0 && no_pipe(data->lex))
			if (ft_exit(data, data->lex->next)== 1)
				continue;
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
				if (!execute_ast(data, data->ast))
					error(data, -1);
				i = 0;
				while (i < total_cmds)
				{
					// wait(NULL);
					waitpid(data->pids[i], &data->exit_stat, 0);
					int return_value = WEXITSTATUS(data->exit_stat);
					printf("return value: %d\n", return_value);
					// printf("pids[%d]:%d", i, data->pids[i]);
					i++;
				}
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
	data.av = &av[1];
	ret = minishell_loop(&data);
	// delete_data(&data);
	return (ret);
}