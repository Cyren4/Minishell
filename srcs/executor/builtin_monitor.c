/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:20:27 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/21 11:08:44 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exec_builtin(t_gen *data, t_lexer *cmd, int fd_exit[2])
{
	int ret;
	char	*c_ret;
	(void)fd_exit;

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
	// else if (ft_strcmp(cmd->content, "exit") == 0)
	//     ret = ft_exit(data, cmd->next);

	c_ret = ft_itoa(ret);
	printf("c_ret: %d\n", ret);
	// write(fd_exit[1], c_ret, ft_strlen(c_ret) + 1);
	// close(fd_exit[1]);
	free(c_ret);
	exit(ret);
	// return (ret);
}