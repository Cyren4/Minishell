/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_exp_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:28:34 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 16:36:09 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tild_exp_norm(t_lexer *elem, t_gen *data)
{
	char	*r_val;

	r_val = NULL;
	if (elem->content[1] == '\0')
		r_val = ft_strdup(data->home);
	else if (elem->content[1] == '/')
	{
		r_val = ft_substr(elem->content, 1, ft_strlen(elem->content) - 1);
		r_val = ft_strjoin(ft_strdup(data->home), r_val);
	}
	else if (ft_strcmp(elem->content, "~+") == 0
		&& get_var_exist(data, "PWD") != NULL)
		r_val = ft_strdup(get_env_var(data, "PWD"));
	else if (ft_strcmp(elem->content, "~-") == 0
		&& get_var_exist(data, "OLDPWD") != NULL)
		r_val = ft_strdup(get_env_var(data, "OLDPWD"));
	return (r_val);
}

int	is_tild_exp(t_lexer *elem, t_gen *data)
{
	char	*r_val;

	if (!elem || !elem->content)
		return (0);
	r_val = NULL;
	if (elem->content[0] == '~')
		r_val = tild_exp_norm(elem, data);
	if (r_val == NULL)
		return (0);
	free(elem->content);
	elem->content = r_val;
	return (1);
}
