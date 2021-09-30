/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insert_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:14:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/28 16:50:11 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	insert_var(char *dst, char *src, int *src_i, t_gen *data)
{
	char	*env_var;
	int		i;
	int		var_len;
	char	*status;

	i = 0;
	if (ft_strncmp(src + *src_i, "$?", 2) == 0)
	{
		var_len = len_int(data->exit_stat);
		status = ft_itoa(data->exit_stat);
		ft_memcpy(dst, status, var_len);
		free(status);
		*src_i += 2;
		return (var_len);
	}
	env_var = malloc(sizeof(char *) * (ft_strlen(src) - *src_i + 1));
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
	free(env_var);
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
		return (len_int(data->exit_stat));
	}
	env_var = malloc(sizeof(char *) * (ft_strlen(src) - *src_i + 1));
	*src_i += 1;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i += 1;
		i++;
	}
	env_var[i] = '\0';
	var_len = ft_strlen(get_env_var(data, env_var));
	free(env_var);
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
		if (content[i] == '"' || content[i] == '\'')
			quote_interpretation(content[i], &inside);
		else if (content[i] == '$' && inside != SIMPLE_Q)
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
