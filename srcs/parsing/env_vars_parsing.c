/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:45:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/30 18:17:14 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (tmp)
		data->paths = ft_split(tmp->content, ':');
	elems = 0;
}

void	add_elem(t_gen *data, char *var_path)
{
	t_env	*new;
	t_env	*head;

	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_split(var_path, '=')[0];
	new->content = ft_substr(var_path, ft_strlen(new->name) + 1,
			ft_strlen(var_path));
	new->next = NULL;
	if (!data->env)
		data->env = new;
	else
	{
		head = data->env;
		while (data->env->next)
			data->env = data->env->next;
		data->env->next = new;
		data->env = head;
	}
}

void	update_SHLVL(t_gen *data)
{
	t_env	*tmp;
	int		curSHLVL;
	
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "SHLVL") == 0)
		{
			curSHLVL = ft_atoi(tmp->content);
			free(tmp->content);
			tmp->content = ft_itoa(curSHLVL + 1);
			return;
		}
		tmp = tmp->next;
	}
}

void	stock_env_vars(t_gen *data, char **env)
{
	int	i;

	data->env = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		// printf("env[%d]: %s\n", i , env[i]);
		add_elem(data, env[i]);
		i++;
	}
	create_paths(data);
}
