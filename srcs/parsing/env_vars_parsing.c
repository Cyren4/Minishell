/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:45:42 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/21 20:38:02 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_paths(t_gen *data)
{
	// t_env	*tmp;
	char	*tmp;

	data->paths = NULL;
	tmp = get_var_exist(data, "PATH");
	// tmp = data->env;
	// while (tmp != NULL)
	// {
	// 	if (ft_strcmp(tmp->name, "PATH") == 0)
	// 		break ;
	// 	tmp = tmp->next;
	// }
	if (tmp)
		data->paths = ft_split(ft_strdup(tmp), ':');
}

void	add_elem(t_gen *data, char *var_path)
{
	t_env	*new;
	t_env	*tmp;
	int		eq_pos;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	eq_pos = occur(var_path, '=', 1);
	new->name = ft_substr(var_path, 0, eq_pos);
	new->content = ft_substr(var_path, eq_pos + 1,
			ft_strlen(var_path) - eq_pos);
	new->next = NULL;
	if (!data->env)
		data->env = new;
	else
	{
		tmp = data->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	update_shlvl(t_gen *data)
{
	t_env	*tmp;
	int		cur_shlvl;

	if (get_var_exist(data, "SHLVL") == NULL)
	{
		add_elem(data, "SHLVL=1");
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "SHLVL") == 0)
		{
			cur_shlvl = ft_atoi(tmp->content);
			ft_free(tmp->content);
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
		add_elem(data, env[i]);
		i++;
	}
	update_shlvl(data);
	data->home = ft_strdup(get_env_var(data, "HOME"));
}
