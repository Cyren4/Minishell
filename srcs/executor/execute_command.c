/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/16 15:52:27 by cramdani         ###   ########.fr       */
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

	if (ast->redir)
		if (!manage_redirs(ast))
			return (0);
	if (ast->cmd->is_builtin == 1 && pipe == 0)
	{
		data->exit_stat = exec_builtin(data, ast->cmd, ast);
		return (data->exit_stat);
	}
	if (!data->paths && !ast->cmd->is_builtin)
	{
		print_error("minishell: ", ast->cmd->content, ": No such file or directory\n");
		return (1);
	}
	pid = fork();
	data->pids[data->tracker] = pid;
	data->tracker++;
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		get_pid(0);
		dup2(ast->fd_in, STDIN_FILENO);
		dup2(ast->fd_out, STDOUT_FILENO);
		if (ast->cmd->is_builtin == 1 && pipe == 1)
			data->exit_stat = exec_builtin(data, ast->cmd, ast);
		else if (!ast->cmd->is_builtin)
		{
			env = env_to_child(data->env);
			cmd = NULL;
			cmd_table = create_command(ast->cmd);
			cmd = is_excve(cmd_table[0], data);
			if (!cmd)
			{
				print_error("minishell: ", ast->cmd->content, ": command not found\n");
				exit(1);
			}
			else
				return (execve(cmd, cmd_table, env));
		}
		exit(1);
	}
	else
	{
		get_pid(pid);
		sig_child();
		if (ast->fd_in != 0)
			close(ast->fd_in);
		if (ast->fd_out != 1)
			close(ast->fd_out);
	}
	return (data->exit_stat);
}
		// waitpid(pid, &status, WUNTRACED | WCONTINUED);
		// if (WIFSIGNALED(status) == 1)
		// {
		// 	if (WTERMSIG(status) == 131)
		// 		printf("segfault")
		// }
