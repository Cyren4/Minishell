/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/21 12:11:32 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "../../includes/minishell.h"

int skip_to_next_quote(t_gen *data, int i)
{
	char quote_type;

	quote_type = 34;
	if (data->parser.std_in[i] == 39)
		quote_type = 39;
	i++;
	while (data->parser.std_in[i])
	{
		if (data->parser.std_in[i] == quote_type)
			break;
		i++; 
	}
	if (i == (int)ft_strlen(data->parser.std_in))
		error(data, QUOTES_UNCLOSED);
	return (i);
}

int is_in_quotes(char *str, int i)
{	
	while (i >= 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
			break;
		i--;
	}
	if (i == -1)
		return 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return i;
		i++;
	}
	return 0;
}

void splitter(t_gen *data)
{
	int i;
	int start;
	int elems;
	char **split_head;
	char *tmp;

	
	tmp = ft_strtrim(data->parser.std_in, " ");
	free(data->parser.std_in);
	data->parser.std_in = ft_substr(tmp, 0, ft_strlen(tmp));
	free(tmp);
	elems = 0;
	i = 0;
	while (data->parser.std_in[i])
	{
		
		if (data->parser.std_in[i] == 39 || data->parser.std_in[i] == 34)
			i = skip_to_next_quote(data, i);
		if (check_charset(data->parser.std_in[i], "|<>") != -1)
			elems+= 2;
		if (data->parser.std_in[i] == ' ')
		{
			elems++;
			while (data->parser.std_in[i] == ' ')
				i++;
		}
		else
			i++;
	}
	elems++;
	data->parser.parsed = (char **)malloc(sizeof(char *) * (elems + 1));
	split_head = data->parser.parsed;
	if (!data->parser.parsed)
		error(data, BAD_MALLOC);
	// data->parser.parsed[elems] = NULL;
	i = 0;
	start = i;
	while (data->parser.std_in[i])
	{
		if (data->parser.std_in[i] == 39 || data->parser.std_in[i] == 34)
			i = skip_to_next_quote(data, i);
		if (check_charset(data->parser.std_in[i], "<>| ") != -1)
		{
			if (data->parser.std_in[i] == ' ')
			{
				*data->parser.parsed = ft_substr(data->parser.std_in, start, i - start);
				data->parser.parsed++;
				while (data->parser.std_in[i] == ' ')
					i++;
				start = i;
			}
			if (check_charset(data->parser.std_in[i], "<>|") != -1)
			{
				*data->parser.parsed = ft_substr(data->parser.std_in, start, i - start);
				data->parser.parsed++;
				*data->parser.parsed = ft_substr(&(data->parser.std_in[i]), 0, 1);
				data->parser.parsed++;
				i++;
				start = i;
			}
		}
		else
			i++;
	}
	*data->parser.parsed = ft_substr(data->parser.std_in, start, i - start);
	data->parser.parsed++;
	*data->parser.parsed = NULL;
	data->parser.parsed = split_head;
}

int main(int ac, char **av)
{
	int i;
	t_gen data;

	data.parser.std_in =ft_strdup(av[1]);
	splitter(&data);
	(void)ac;

	i = 0;
	while (data.parser.parsed[i] != NULL)
	{
		printf("%s\n", data.parser.parsed[i]);
		i++;
	}
}

// void display_prompt(t_gen *data)
// {
// 	int i;

// 	data->parser.std_in = readline("minishell $ ");
// 	splitter(data);
// 	i = -1;
// 	while (data->parser.parsed[++i] != NULL)
// 		printf("parsed[%d]: %s\n", i, data->parser.parsed[i]);
// }