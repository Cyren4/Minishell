/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/21 11:11:35 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **create_command(t_lexer *cmd)
{
	t_lexer *head;
	int len;
	char **cmd_table;

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

int execute_command(t_gen *data, t_tree *ast)
{
	int pid;
	char **cmd_table;
	char *cmd;
	char	**env;
	int fd_exit[2];
	char buf[100];

	if (ast->redir)
		manage_redirs(ast);
	pipe(fd_exit);
	pid = fork();
	data->pids[data->tracker] = pid;
	data->tracker++;
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		close(fd_exit[0]);
		dup2(ast->fd_in, STDIN_FILENO);
		if (ast->fd_in > 0)
			close(ast->fd_in);
		dup2(ast->fd_out, STDOUT_FILENO);
		if (ast->cmd->is_builtin == 1)
			data->exit_stat = exec_builtin(data, ast->cmd, fd_exit);
		else
		{
			env = env_to_child(data->env);
			cmd = NULL;
			cmd_table = create_command(ast->cmd);
			cmd = is_excve(cmd_table[0], data);
			if (!cmd)
				ft_putstr_fd("bad command\n", ast->fd_out);
			else
				execve(cmd, cmd_table, env);
			return(1);
			// free_tab(env);
		}
	}
	else
	{
		close(fd_exit[1]);
		read(fd_exit[0], buf, 100);
		data->exit_stat = ft_atoi(buf);
		if (ast->fd_in != 0)
			close(ast->fd_in);
		if (ast->fd_out != 1)
			close(ast->fd_out);
	}
	return (data->exit_stat);
}