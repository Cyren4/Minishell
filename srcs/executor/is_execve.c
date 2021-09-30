/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/30 16:26:30 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char *is_excve(char *command, t_gen *data)
{
	int i;
	char *cmd_path;
	
	i = 0;
	cmd_path = NULL;
	if (lstat(command, NULL) == 0)
		return (command);
	while (data->paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(data->paths[i], "/"), command);
		if (lstat(cmd_path, NULL) == 0)
			break ;
		i++;
		if (cmd_path)
			free(cmd_path);
	}
	return (cmd_path);
}