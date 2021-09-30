/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:23:32 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/30 18:05:26 by vbaron           ###   ########.fr       */
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
	
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		cmd = NULL;
		cmd_table = create_command(ast->cmd);
		display_array(cmd_table);
		cmd = is_excve(cmd_table[0], data);
		if (!cmd)
			return (0);
		execve(cmd, cmd_table, NULL);
	}
	return (1);
}