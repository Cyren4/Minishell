/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insert_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:14:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 20:15:10 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// insert var
int	insert_var(char *dst, char *src, int *src_i, t_gen *data)
{
	char	*env_var;
	int		i;
	int		var_len;
	char	*status;

	i = 0;
	if (ft_strncmp(src + *src_i, "$?", 2) == 0)
	{
		// var_len = len_int(data->exit_stat);
		status = ft_itoa(get_exit_stat(-1));
		var_len = ft_strlen(status);
		ft_memcpy(dst, status, var_len);
		ft_free(status);
		*src_i += 2;
		return (var_len);
	}
	env_var = malloc(sizeof(char *) * (ft_strlen(src) - *src_i + 1));
	if (!env_var)
		return (-1);
	*src_i += 1;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i += 1;
		i++;
	}
	env_var[i] = '\0';
	var_len = ft_strlen(get_env_var(data, env_var));
	ft_memcpy(dst, get_env_var(data, env_var), var_len);
	ft_free(env_var);
	return (var_len);
}

int	var_size(char *src, int *src_i, t_gen *data)
{
	char	*env_var;
	int		i;
	int		var_len;

	i = 0;
	if (ft_strncmp(src + *src_i, "$?", 2) == 0)
	{
		*src_i += 2;
		return (len_int(get_exit_stat(-1)));
	}
	env_var = malloc(sizeof(char *) * (ft_strlen(src) - *src_i + 1));
	if (!env_var)
		return (-1);
	*src_i += 1;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i += 1;
		i++;
	}
	env_var[i] = '\0';
	var_len = ft_strlen(get_env_var(data, env_var));
	ft_free(env_var);
	return (var_len);
}

int	real_size(char *content, t_gen *data)
{
	int		total_size;
	int		inside;
	int		i;

	i = 0;
	inside = NO_Q;
	total_size = 0;
	while (content[i])
	{
		if ((content[i] == '"' && inside != SIMPLE_Q)
			|| (content[i] == '\'' && inside != DOUBLE_Q))
			quote_interpretation(content[i], &inside);
		if (content[i] == '$' && inside != SIMPLE_Q
			&& valid_e(content, i))
		{
			total_size += var_size(content, &i, data);
			continue ;
		}
		else
			total_size++;
		i++;
	}
	return (total_size);
}
