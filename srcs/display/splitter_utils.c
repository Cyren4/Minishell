/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:11:04 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/28 16:05:11 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
int	skip_to_next_quote(t_gen *data, int i)
{
	char	quote_type;

	quote_type = 34;
	if (data->parser.std_in[i] == 39)
		quote_type = 39;
	i++;
	while (data->parser.std_in[i])
	{
		if (data->parser.std_in[i] == quote_type)
			break ;
		i++;
	}
	if (i == (int)ft_strlen(data->parser.std_in))
	{
		error(data, QUOTES_UNCLOSED);
		return (-1);
	}
	return (i);
}

int	is_in_quotes(char *str, int i)
{	
	while (i >= 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
			break ;
		i--;
	}
	if (i == -1)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (0);
}
*/