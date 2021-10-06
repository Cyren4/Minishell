/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:45:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/06 21:50:39 by cramdani         ###   ########.fr       */
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
	int		eq_pos;

	new = (t_env *)malloc(sizeof(t_env));
	eq_pos = occur(var_path, '=', 1);
	new->name = ft_substr(var_path, 0, eq_pos);
	new->content = ft_substr(var_path, eq_pos + 1,
			ft_strlen(var_path) - eq_pos - 1);
	new->next = NULL;
	if (new->name && ft_strcmp(new->name, "PWD") == 0)
		data->pwd = ft_strdup(new->content);
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

void	update_shlvl(t_gen *data)
{
	t_env	*tmp;
	int		cur_shlvl;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "SHLVL") == 0)
		{
			cur_shlvl = ft_atoi(tmp->content);
			free(tmp->content);
			tmp->content = ft_itoa(cur_shlvl + 1);
			return ;
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
	update_shlvl(data);
	// display_env_vars(data->env);
}
