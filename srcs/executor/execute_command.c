/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/28 17:02:16 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_command(t_lexer *cmd)
{
	t_lexer	*head;
	int		len;
	char	**cmd_table;

	if (!cmd->content)
		return (NULL);
	len = calculate_len(cmd);
	head = cmd;
	cmd_table = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd_table)
		return (NULL);
	len = 0;
	while (head)
	{
		cmd_table[len] = ft_strdup(head->content);
		len++;
		head = head->next;
	}
	cmd_table[len] = NULL;
	return (cmd_table);
}

int	no_pipe_exec(t_gen *data, t_tree *ast, int pipe)
{
	data->cmd = NULL;
	if (!ast->cmd)
		return (get_exit_stat(1));
	if (ast->cmd->is_builtin == 1 && pipe == 0)
		return (get_exit_stat(exec_builtin(data, ast->cmd, ast)));
	if (!data->paths && !ast->cmd->is_builtin)
	{
		print_error("minishell: ", ast->cmd->content,
			": No such file or directory\n");
		return (get_exit_stat(127));
	}
	data->cmd_table = create_command(ast->cmd);
	if (!ast->cmd->is_builtin && data->cmd_table)
		data->cmd = is_excve(data->cmd_table[0], data);
	if (ast->cmd->is_builtin == 0 && data->cmd == NULL)
	{
		free_tab(data->cmd_table);
		return (get_exit_stat(-1));
	}
	return (-1);
}

void	exec_child(t_gen *data, t_tree *ast, int pipe)
{
	char	**env;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	get_pid(0);
	dup2(ast->fd_in, STDIN_FILENO);
	dup2(ast->fd_out, STDOUT_FILENO);
	if (ast->cmd->is_builtin == 1 && pipe == 1)
		get_exit_stat(exec_builtin(data, ast->cmd, ast));
	close_pipes(data->ast);
	if (!ast->cmd->is_builtin)
	{
		env = env_to_child(data->env);
		execve(data->cmd, data->cmd_table, env);
	}
	clean_child(data);
	if (!data->cmd)
		exit(get_exit_stat(127));
	exit(1);
}

void	exec_parent(t_gen *data, t_tree *ast, int pid)
{
	sig_child();
	get_pid(pid);
	if (ast->fd_in != 0 && ast->fd_in != -1)
		close(ast->fd_in);
	if (ast->fd_out != 1 && ast->fd_out != -1)
		close(ast->fd_out);
	free_tab(data->cmd_table);
	free(data->cmd);
}

int	execute_command(t_gen *data, t_tree *ast, int pipe)
{
	int		pid;

	data->pids[data->tracker] = -1;
	if (ast->redir)
	{
		if (!manage_redirs(ast, data))
		{
			close_pipes(ast);
			return (get_exit_stat(1));
		}
	}
	if (no_pipe_exec(data, ast, pipe) != -1)
		return (get_exit_stat(-1));
	pid = fork();
	data->pids[data->tracker] = pid;
	data->tracker++;
	if (pid < 0)
		return (0);
	else if (pid == 0)
		exec_child(data, ast, pipe);
	else
		exec_parent(data, ast, pid);
	return (get_exit_stat(-1));
}
