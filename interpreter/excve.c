/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:18:09 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/22 10:46:58 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void ft_excve(char *command, char **args, t_gen *data)
{
	int i;
	
	i = 0;
	while (data->paths[i])
	{
		execve(ft_strjoin(data->paths[i], command), args, data->paths);
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
		if (ft_strcmp(tmp->name, "PATHS"))
			break;
		tmp = tmp->next;
	}
	elems = 0;
	data->paths = ft_split(tmp->content, ':');
}

int main(int ac, char **av, char **env)
{
	t_gen data;

	stock_env_vars(&data, env);
	create_paths(&data);
	ft_excve(av[1], &av[1], &data);
}