/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/28 16:53:33 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*mini_error_handler(char *str, int type, struct stat *state)
{
	if (type == 1)
	{
		print_error("minishell: ", str, ": command not found\n");
		get_exit_stat(127);
	}
	if (type == 2)
	{
		if (S_ISDIR(state->st_mode))
			print_error("minishell: ", str, ": Is a directory\n");
		else
			print_error("minishell: ", str, ": Permission denied\n");
		get_exit_stat(126);
		free(state);
	}
	return (NULL);
}

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
		mini_error_handler(command, 1, state);
	return (cmd_path);
}

char	*is_excve(char *command, t_gen *data)
{
	char		*cmd_path;
	struct stat	*state;

	if (ft_strlen(command) == 0)
	{
		print_error("minishell: ", command, ": command not found\n");
		get_exit_stat(127);
		return (NULL);
	}
	state = malloc(sizeof(struct stat));
	if (!state || !data->paths)
		return (NULL);
	if (lstat(command, state) == 0 && (S_ISDIR(state->st_mode)
			|| !(state->st_mode & S_IXUSR)))
		return (mini_error_handler(command, 2, state));
	if (lstat(command, state) == 0)
	{
		free(state);
		return (ft_strdup(command));
	}
	cmd_path = check_command(command, data, state);
	free(state);
	return (cmd_path);
}
