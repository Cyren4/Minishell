/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:09:56 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 19:11:36 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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