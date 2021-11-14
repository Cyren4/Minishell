/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/14 19:17:59 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env_exp(char *cmd, int eq_pos)
{
	t_env	*new;

	if (eq_pos < 0)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_substr(cmd, 0, eq_pos);
	new->content = ft_substr(cmd, eq_pos + 1, ft_strlen(cmd) - eq_pos - 1);
	new->next = NULL;
	return (new);
}

int	unvalid_exp(char *env)
{
	int	i;
	int	eq_pos;

	eq_pos = occur(env, '=', 1);
	i = 0;
	if (*env == '=')
		return (1);
	while (env && env[i])
	{
		if (i < eq_pos && !ft_isalnum(env[i]) && env[i] != '_' && env[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

void	special_case(t_gen *data, t_env *new)
{
	if (ft_strcmp("PS1", new->name) == 0)
	{
		free(data->prompt);
		data->prompt = ft_strdup(new->content);
	}
}

void	add_env(t_gen *data, t_env *new)
{
	t_env	*tmp;

	if (new == NULL)
		return ;
	tmp = data->env;
	while (tmp->next != NULL)
	{
		special_case(data, new);
		if (ft_strcmp(tmp->name, new->name) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(new->content);
			free_env(new);
			return ;
		}
		tmp = tmp->next;
	}
	new->next = data->env;
	data->env = new;
}

int	ft_export(t_gen *data, t_lexer *cmd, t_tree *ast)
{
	t_lexer	*tmp;
	t_env	*new;
	int		ret;

	ret = EXIT_SUCCESS;
	tmp = cmd;
	if (cmd == NULL)
		ft_env(data, "declare -x ", ast);
	while (cmd != NULL && tmp != NULL)
	{
		if (unvalid_exp(cmd->content))
		{
			print_error("export: `", cmd->content,"': not a valid identifier\n");
			ret = EXIT_FAILURE;
		}
		else
		{
			new = NULL;
			new = create_env_exp(tmp->content, occur(tmp->content, '=', 1));
			add_env(data, new);
		}
		tmp = tmp->next;
	}
	return (ret);
}
