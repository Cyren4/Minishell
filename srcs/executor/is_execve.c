/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/26 12:51:45 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_command(char *command, t_gen *data, struct stat *state)
{
	char	*cmd_path;
	int		i;
	char	*tmp;

	cmd_path = NULL;
	i = 0;
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
	if (cmd_path == NULL)
		print_error("minishell: ", command, ": command not found\n");
	get_exit_stat(127);
	return (cmd_path);
}

char	*is_excve(char *command, t_gen *data)
{
	char		*cmd_path;
	struct stat	*state;

	if (!data->paths)
		return (NULL);
	state = malloc(sizeof(struct stat));
	if (!state)
		return (NULL);
	if (lstat(command, state) == 0 && S_ISDIR(state->st_mode))
	{
		print_error("minishell: ", command, ": is a directory\n");
		get_exit_stat(126);
		free(state);
		return (NULL);
	}
	if (lstat(command, state) == 0)
	{
		print_error("minishell: ", command, ": command not found\n");
		free(state);
		return (ft_strdup(command));
	}
	cmd_path = check_command(command, data, state);
	free(state);
	return (cmd_path);
}
