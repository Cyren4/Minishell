/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:20:27 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/30 16:46:56 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_gen *data, t_lexer *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->content, "echo") == 0)
		ret = ft_echo(cmd->next);
	else if (ft_strcmp(cmd->content, "cd") == 0)
		ret = ft_cd(data, cmd->next);
	else if (ft_strcmp(cmd->content, "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->content, "export") == 0)
		ret = ft_export(data, cmd->next);
	else if (ft_strcmp(cmd->content, "unset") == 0)
		ret = ft_unset(data, cmd->next);
	else if (ft_strcmp(cmd->content, "env") == 0)
		ret = ft_env(data, "");
	else if (ft_strcmp(cmd->content, "exit") == 0)
	{
	    ret = ft_exit(data, cmd->next);
		// if (ret == 1)
		// 	rl_replace_line();
	}
	return (ret);
}
