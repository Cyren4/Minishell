/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:45:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/18 17:16:26 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_elem(t_gen *data, char *var_path)
{
	t_env *new;
	t_env *head;

	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_split(var_path, '=')[0];
	new->content = ft_substr(var_path, ft_strlen(new->name) + 1, ft_strlen(var_path));
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

	i = 0;
	while (env[i])
	{
		add_elem(data, env[i]);
		i++;
	}
	// display_env_vars(data->env);
}