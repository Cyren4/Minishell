/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/26 17:45:42 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	unvalid_exp(char *env, int *concat)
{
	int	i;
	int	eq_pos;
	int	plus_pos;

	if (ft_strcmp(env, "") == 0)
		return (1);
	eq_pos = occur(env, '=', 1);
	if (eq_pos == -1)
		eq_pos = ft_strlen(env);
	plus_pos = occur(env, '+', 1);
	if (plus_pos != -1 && plus_pos == eq_pos - 1)
		*concat = 1;
	i = 0;
	if (*env == '=')
		return (1);
	while (env && env[i])
	{
		if ((i == 0 && !(ft_isalpha(env[i]) || env[i] == '_'))
			|| (i < eq_pos - *concat && !ft_isalnum(env[i])
				&& env[i] != '_' && env[i] != '='))
			return (1);
		i++;
	}
	return (0);
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

void	export_norm(t_lexer *cmd, int *concat, int *ret)
{
	if (unvalid_exp(cmd->content, concat))
	{
		print_error("export: `", cmd->content,
			"': not a valid identifier\n");
		*ret = EXIT_FAILURE;
	}
}

int	ft_export(t_gen *data, t_lexer *cmd, t_tree *ast)
{
	t_lexer	*tmp;
	t_env	*new;
	int		ret;
	int		concat;

	ret = EXIT_SUCCESS;
	tmp = cmd;
	if (cmd == NULL)
		env_export(data, ast);
	while (cmd != NULL && tmp != NULL)
	{
		concat = 0;
		export_norm(tmp, &concat, &ret);
		if (!unvalid_exp(cmd->content, &concat))
		{
			new = NULL;
			new = create_env_exp(data, tmp->content,
					occur(tmp->content, '=', 1), concat);
			add_env(data, new);
		}
		tmp = tmp->next;
	}
	return (ret);
}
