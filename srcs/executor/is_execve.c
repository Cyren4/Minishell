/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/23 17:15:53 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*is_excve(char *command, t_gen *data)
{
	int			i;
	char		*cmd_path;
	struct stat	*state;
	char *tmp;

	if (!data->paths)
		return (NULL);
	i = 0;
	cmd_path = NULL;
	state = malloc(sizeof(struct stat));
	if (!state)
		return (NULL);
	if (lstat(command, state) == 0)
	{
		free(state);
		return (command);
	}
	while (data->paths[i])
	{
		
		tmp = ft_strjoin(data->paths[i], "/");
		cmd_path = ft_strjoin(tmp, command);
		free(tmp);
		if (lstat(cmd_path, state) == 0)
			break ;
		i++;
		if (cmd_path)
		{
			free(cmd_path);
			cmd_path = NULL;
		}
	}
	free(state);
	return (cmd_path);
}
