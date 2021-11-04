/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/30 16:46:44 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env(t_env *env)
{
	free(env->content);
	free(env->name);
	free(env);
}

int	unvalid_env(char *env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	delete_env(t_gen *data, char *var)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = data->env;
	if (ft_strcmp(tmp->name, var) == 0)
	{
		data->env = data->env->next;
		free_env(tmp);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->name, var) == 0)
		{
			tmp2 = tmp->next->next;
			free_env(tmp->next);
			tmp->next = tmp2;
			if (ft_strcmp("PS1", var) == 0)
			{
				free(data->prompt);
				data->prompt = ft_strdup("");
			}
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_gen *data, t_lexer *cmd)
{
	t_lexer	*tmp;
	int		ret;

	tmp = cmd;
	ret = EXIT_SUCCESS;
	while (tmp != NULL)
	{
		if (unvalid_env(cmd->content))
		{
			printf("unset: `%s': not a valid identifier\n", cmd->content);
			ret = EXIT_FAILURE;
		}
		else
			delete_env(data, tmp->content);
		tmp = tmp->next;
	}
	return (ret);
}
