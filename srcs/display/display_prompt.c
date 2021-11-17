/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/17 18:31:04 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		error(data, QUOTES_UNCLOSED);
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

void	norm_split(t_gen *data, int i, int start, char **split_head)
{
	*data->parser.parsed = ft_substr(data->parser.std_in, start, i - start);
	data->parser.parsed++;
	*data->parser.parsed = NULL;
	data->parser.parsed = split_head;
}

/*
	t[0] = i
	t[1] = start
	d = data
*/
void	splitter2(t_gen *d, int elems)
{
	int		t[2];
	char	**split_head;

	d->parser.parsed = (char **)malloc(sizeof(char *) * (elems + 1));
	split_head = d->parser.parsed;
	if (!d->parser.parsed)
		error(d, BAD_MALLOC);
	t[0] = 0;
	t[1] = t[0];
	while (d->parser.std_in[t[0]])
	{
		if (d->parser.std_in[t[0]] == 39 || d->parser.std_in[t[0]] == 34)
			t[0] = skip_to_next_quote(d, t[0]);
		if (d->parser.std_in[t[0]] == ' ')
		{
			*d->parser.parsed = ft_substr(d->parser.std_in, t[1], t[0] - t[1]);
			d->parser.parsed++;
			while (d->parser.std_in[t[0]] == ' ')
				t[0]++;
			t[1] = t[0];
		}
		else
			t[0]++;
	}
	norm_split(d, t[0], t[1], split_head);
}

void	splitter(t_gen *data)
{
	int		i;
	int		elems;
	char	*tmp;

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
	splitter2(data, elems);
}

void	display_prompt(t_gen *data)
{

	data->parser.std_in = readline(data->prompt);
	if (!data->parser.std_in)
	{
		printf("\b\b  \b\bexit\n");
		delete_data(data);
		exit(get_exit_stat(-1));
	}
	if (ft_strcmp(data->parser.std_in, "") != 0)
		add_history(data->parser.std_in);
	if (is_empty(data->parser.std_in) == 1)
	{
		ft_free(data->parser.std_in);
		display_prompt(data);
	}
	splitter(data);
	if (data->status != 1)
	{
		data->status = 1;
		ft_free(data->parser.std_in);
		free_tab(data->parser.parsed);
		exit(get_exit_stat(1));
		display_prompt(data);
	}
}
