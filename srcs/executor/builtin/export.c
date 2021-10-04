/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/04 11:44:39 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env(char *cmd, int eq_pos)
{
	t_env	*new;

	if (eq_pos < 0)
		return NULL;
	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_substr(cmd, 0, eq_pos);
	new->content = ft_substr(cmd, eq_pos + 1, ft_strlen(cmd) - eq_pos - 1);
	new->next = NULL;
	return new;
}

int	unvalid_exp(char *env)
{
	int	i;
	int	eq_pos;

	eq_pos = occur(env, '=', 1);
	i = 0;
	if (*env ==  '=')
		return (1);
	while (env && env[i])
	{
		if ((!ft_isalnum(env[i]) && env[i] != '_' && env[i] != '=' && !ft_isspace(env[i]))
			|| ((ft_isspace(env[i]) && i < eq_pos)))
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
	//gerer le PWD et OLPWD 
	//-> a chaque cd le pwd et oldpwd se met a jour
	//pwd prend le pwd actuel et old pwd prend l'ancien
}

void	add_env(t_gen *data, t_env *new)
{
	t_env	*tmp;

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

void ft_export(t_gen *data, t_lexer *cmd)
{
	t_lexer *tmp;
	t_env	*new;

	tmp = cmd;
	data->exit_stat = 0;
	if (cmd == NULL)
	{
		// echo env with declare -x suffix
		// if (fork() == 0)
			// execve("declare", {"declare -x", NULL}, data->env);
		return;
	}
	while (tmp != NULL)
	{
		if (unvalid_exp(cmd->content))
		{
			printf("export: `%s': not a valid identifier\n", cmd->content);
			data->exit_stat = 1;
		}
		else
		{
			new = NULL;
			new = create_env(tmp->content, occur(tmp->content, '=', 1) );
			if (new != NULL)
				add_env(data, new);
		}
		tmp = tmp->next;
	}
}
