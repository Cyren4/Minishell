/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:42:47 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/05 15:53:48 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char *ret;

	ret = get_var_exist(gen, var);
	if (ret == NULL)
		return ("");
	return (ret); 
}
