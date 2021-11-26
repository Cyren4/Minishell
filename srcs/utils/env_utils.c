/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:42:47 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/26 11:01:28 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

char	*get_var_exist(t_gen *gen, char *var)
{
	t_env	*tmp_env;

	tmp_env = gen->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, var) == 0)
			return (tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*get_env_var(t_gen *gen, char *var)
{
	char	*ret;

	ret = get_var_exist(gen, var);
	if (ret == NULL)
		return ("");
	return (ret);
}

int	size_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**env_to_child(t_env *env)
{
	int		i;
	char	**tab;
	t_env	*tmp;

	tab = malloc(sizeof(char *) * (size_env(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = join_sep(tmp->name, tmp->content, '=');
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
