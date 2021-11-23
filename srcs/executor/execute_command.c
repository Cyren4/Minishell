/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/23 17:56:11 by vbaron           ###   ########.fr       */
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
		cmd_table[len] = ft_strdup(head->content);
		len++;
		head = head->next;
	}
	cmd_table[len] = NULL;
	return (cmd_table);
}

int	execute_command(t_gen *data, t_tree *ast, int pipe)
{
	int		pid;
	char	**env;

	if (ast->redir)
		if (!manage_redirs(ast))
			return (0);
	if (!ast->cmd)
		return (1);
	if (ast->cmd->is_builtin == 1 && pipe == 0)
		return(data->exit_stat = exec_builtin(data, ast->cmd, ast));
	if (!data->paths && !ast->cmd->is_builtin)
	{
		print_error("minishell: ", ast->cmd->content, ": No such file or directory\n");
		return (get_exit_stat(127));
	}
	data->cmd_table = create_command(ast->cmd);
	data->cmd = is_excve(data->cmd_table[0], data);
	if (ast->cmd->is_builtin == 0 &&  data->cmd == NULL)
	{
		display_array(data->cmd_table);
		free_tab(data->cmd_table);
		print_error("minishell: ", ast->cmd->content, ": command not found\n");
		return (get_exit_stat(127));
	}
	pid = fork();
	data->pids[data->tracker] = pid;
	data->tracker++;
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		get_pid(0);
		dup2(ast->fd_in, STDIN_FILENO);
		dup2(ast->fd_out, STDOUT_FILENO);
		close_pipes(data->ast);
		if (ast->cmd->is_builtin == 1 && pipe == 1)
			get_exit_stat(exec_builtin(data, ast->cmd, ast));
		else if (!ast->cmd->is_builtin)
		{
			env = env_to_child(data->env);
			execve(data->cmd, data->cmd_table, env);
		}
		clean_child(data);
		ft_free(data->prompt);
		if (!data->cmd)
			exit(get_exit_stat(127));
		exit(1);
	}
	else
	{
		sig_child();
		get_pid(pid);
		if (ast->fd_in != 0)
			close(ast->fd_in);
		if (ast->fd_out != 1)
			close(ast->fd_out);
		free_tab(data->cmd_table);
		free(data->cmd);
	}
	return (get_exit_stat(-1));
}
		// printf("main process command: %s - ast->fd_out: %d\n", ast->cmd->content, fcntl(ast->fd_out, F_GETFD));
		// printf("main process command: %s - ast->fd_in: %d\n", ast->cmd->content, fcntl(ast->fd_out, F_GETFD));
		// waitpid(pid, &status, WUNTRACED | WCONTINUED);
		// if (WIFSIGNALED(status) == 1)
		// {
		// 	if (WTERMSIG(status) == 131)
		// 		printf("segfault")
		// }
