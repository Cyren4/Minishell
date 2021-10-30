/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/30 14:39:25 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_command(t_lexer *cmd)
{
	t_lexer	*head;
	int		len;
	char	**cmd_table;

	head = cmd;
	len = 0;
	while (head != NULL)
	{
		head = head->next;
		len++;
	}
	head = cmd;
	cmd_table = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd_table)
		return (NULL);
	len = 0;
	while (head)
	{
		cmd_table[len] = head->content;
		len++;
		head = head->next;
	}
	cmd_table[len] = NULL;
	return (cmd_table);
}

int	execute_command(t_gen *data, t_tree *ast, int pipe)
{
	int		pid;
	char	**cmd_table;
	char	*cmd;
	char	**env;

	if (ast->cmd->is_builtin == 1 && pipe == 0)
		data->exit_stat = exec_builtin(data, ast->cmd);
	if (ast->redir)
		manage_redirs(ast);
	pid = fork();
	data->pids[data->tracker] = pid;
	data->tracker++;
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		dup2(ast->fd_in, STDIN_FILENO);
		dup2(ast->fd_out, STDOUT_FILENO);
		if (ast->cmd->is_builtin == 1 && pipe == 1)
			data->exit_stat = exec_builtin(data, ast->cmd);
		else if (!ast->cmd->is_builtin)
		{
			env = env_to_child(data->env);
			cmd = NULL;
			cmd_table = create_command(ast->cmd);
			cmd = is_excve(cmd_table[0], data);
			if (!cmd)
				ft_putstr_fd("bad command\n", ast->fd_out);
			else
				return (execve(cmd, cmd_table, env));
		}
		exit(1);
	}
	else
		if (ast->fd_out != 1)
			close(ast->fd_out);
	return (data->exit_stat);
}
