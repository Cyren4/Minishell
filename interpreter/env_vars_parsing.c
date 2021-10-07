/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:45:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/03 17:27:55 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void display_env_vars(t_env *envs)
{
	t_env *head;

	head = envs;
	
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->content);
		envs = envs->next;
	}
	envs = head;
}

//modifié car ft_split risque de leak 
//-> alloue aussi de la memoire pour ce qu'il y a apres =
void add_elem(t_gen *data, char *var_path)
{
	t_env *new;
	t_env *head;
	int		eq_pos;
	
	eq_pos = occur(var_path, '=', 1);
	new = (t_env *)malloc(sizeof(t_env));
	// new->name = ft_split(var_path, '=')[0];
	// new->content = ft_substr(var_path, ft_strlen(new->name) + 1, ft_strlen(var_path));
	new->name = ft_substr(var_path, 0, eq_pos);
	new->content = ft_substr(var_path, eq_pos + 1, ft_strlen(var_path) - eq_pos - 1);
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

void stock_env_vars(t_gen *data, char **env)
{
	int i;

	data->env = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		add_elem(data, env[i]);
		i++;
	}
	// display_env_vars(data->env);
}