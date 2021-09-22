/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 17:26:51 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void display_array(char **path)
{
	int i;
	i = 0;

	while (path[i])
	{
		printf("array[%i]: %s\n", i, path[i]);
		i++;
	}
}

void ft_excve(char *command, char **args, t_gen *data)
{
	int i;
	
	i = 0;

	execve(command, args, data->paths);
	while (data->paths[i])
	{
		execve(ft_strjoin(ft_strjoin(data->paths[i], "/"), command), args, data->paths);
		i++;
	}
}

void create_paths(t_gen *data)
{
	t_env *tmp;
	int elems;

	tmp = data->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			break;
		tmp = tmp->next;
	}
	data->paths = ft_split(tmp->content, ':');
	elems = 0;
	display_array(data->paths);
}

int main(int ac, char **av, char **envs)
{
	t_gen data;
	int i;

	i = 0;
	stock_env_vars(&data, envs);
	create_paths(&data);
	ft_excve(av[1], &av[1], &data);
}