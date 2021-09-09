/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:50:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/09 20:43:39 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{
	t_command cmd;
	int i;
	char *argv[] = {"ls", NULL};
	char *path_list[] = {"PATH=/Users/vbaron/.brew/bin/", "/Users/vbaron/.brew/bin/", "/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/sbin/", "/sbin/", "/usr/local/go/bin/", "/usr/local/munki/", NULL};

	cmd.echo.n = 0;
	cmd.echo.str = ft_substr("Hello World!", 0, ft_strlen("Hello World!"));
	i = 0;
	// ft_echo(&(cmd.echo));
	// exec_command(argv, env);
	while (path_list[i])
	{
		execve(ft_strjoin(path_list[i], argv[0]), argv, NULL);
		i++;
	}
	stat("ls", NULL);
	return(0);
}
