/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:20:27 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/26 11:50:45 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_gen *data, t_lexer *cmd, t_tree *ast)
{
	int	ret;

	ret = 0;
	if ((ft_strcmp(cmd->content, "pwd") == 0
			|| ft_strcmp(cmd->content, "env") == 0) && cmd->next != NULL)
	{
		print_error(cmd->content, ": too many arguments\n", NULL);
		ret = 1;
	}
	else if (ft_strcmp(cmd->content, "echo") == 0)
		ret = ft_echo(cmd->next, ast);
	else if (ft_strcmp(cmd->content, "cd") == 0)
		ret = ft_cd(data, cmd->next);
	else if (ft_strcmp(cmd->content, "pwd") == 0)
		ret = ft_pwd(ast);
	else if (ft_strcmp(cmd->content, "export") == 0)
		ret = ft_export(data, cmd->next, ast);
	else if (ft_strcmp(cmd->content, "unset") == 0)
		ret = ft_unset(data, cmd->next);
	else if (ft_strcmp(cmd->content, "env") == 0)
		ret = ft_env(data, ast);
	else if (ft_strcmp(cmd->content, "exit") == 0)
		ret = ft_exit(data, cmd->next);
	get_exit_stat(ret);
	return (ret);
}
