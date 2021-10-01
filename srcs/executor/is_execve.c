/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/01 16:52:43 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char *is_excve(char *command, t_gen *data)
{
	int i;
	char *cmd_path;
	struct stat *state;
	
	i = 0;
	cmd_path = NULL;
	state = malloc(sizeof(struct stat));
	if (!state)
		return (NULL);
	if (lstat(command, state) == 0)
		return (command);
	while (data->paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(data->paths[i], "/"), command);
		if (lstat(cmd_path, state) == 0)
			break ;
		i++;
		if (cmd_path)
			free(cmd_path);
	}
	return (cmd_path);
}