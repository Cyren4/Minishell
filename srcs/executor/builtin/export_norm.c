/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:10:20 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 23:11:56 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env_exp(t_gen *data, char *cmd, int eq_pos, int cat)
{
	t_env	*new;
	char	*tmp;

	if (eq_pos < 0)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_substr(cmd, 0, eq_pos - cat);
	new->content = ft_substr(cmd, eq_pos + 1, ft_strlen(cmd) - eq_pos - cat);
	new->next = NULL;
	if (get_var_exist(data, new->name) != NULL && cat == 1)
	{
		tmp = ft_strjoin(get_env_var(data, new->name), new->content);
		free(new->content);
		new->content = tmp;
	}
	return (new);
}

void	special_case(t_gen *data, t_env *new)
{
	if (ft_strcmp("PS1", new->name) == 0)
	{
		free(data->prompt);
		data->prompt = ft_strdup(new->content);
	}
}
