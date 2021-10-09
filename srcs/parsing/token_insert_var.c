/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insert_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:14:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/09 20:46:40 by cramdani         ###   ########.fr       */
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

// retourne 1 s'il y a l'option -n
int		strcpy_nospace(char *dst, char *src, int *var_len)
{
	char	*src1;
	int		ret;
    int		i;
	int		j;

	ret = 0;
	src1 = ft_strtrim(src, " \t\v\f\r\n");
	if (dst == NULL && src == NULL)
		return (ret);
	i = 0;
	j = 0;
	if (ft_strncmp(src1, "-n ", 2) == 0 && ft_isspace(src1[2]))
	{
		ret = 1;
		i += 2;
		while (ft_isspace(src1[i]))
			i++;
	}
	while (src1[i])
	{
		if (!ft_isspace(src1[i]) || !ft_isspace(src1[i + 1]))
		{
			dst[j] = src1[i];
			j++;	
		}
		i++;
	}
	dst[j] = '\0';
	free(src1);
	*var_len = j;
	return (ret);
}

t_lexer	*add_opt_lex(t_lexer *lst)
{
	t_lexer	*new;
	t_lexer	*tmp;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = ft_strdup("-n");
	new->is_builtin = 0;
	new->next = NULL;
	if (lst == NULL)
		return (new);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

int	insert_var_noquote(char *dst, char *src, int *src_i, t_gen *data)
{
	char	*env_var;
	int		i;
	int		var_len;

	i = 0;
	env_var = malloc(sizeof(char *) * (ft_strlen(src) - *src_i + 1));
	*src_i += 1;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i += 1;
		i++;
	}
	env_var[i] = '\0';
	if (strcpy_nospace(dst, get_env_var(data, env_var), &var_len))
	{
	// 	t_lexer *tmp = data->lex;
	// 	while (tmp->next != NULL)
	// 	{
	// 	if(tmp->content)
	// 		printf("|%s|\n", tmp->content);
	// 	tmp = tmp->next;
	// }
		data->lex = add_opt_lex(data->lex);
	}
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
