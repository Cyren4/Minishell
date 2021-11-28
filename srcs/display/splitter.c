/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:09:56 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/28 16:02:33 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* old version splitter
void	norm_split(t_gen *data, int i, int start, char **split_head)
{
	*data->parser.parsed = ft_substr(data->parser.std_in, start, i - start);
	data->parser.parsed++;
	*data->parser.parsed = NULL;
	data->parser.parsed = split_head;
}

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

void	trim_parser(t_gen *data)
{
	char	*tmp;

	tmp = ft_strtrim(data->parser.std_in, " ");
	free(data->parser.std_in);
	data->parser.std_in = ft_substr(tmp, 0, ft_strlen(tmp));
	free(tmp);
}

void	splitter(t_gen *data)
{
	int		i;

	trim_parser(data);
	data->elems = 0;
	i = 0;
	while (data->parser.std_in[i])
	{
		if (data->parser.std_in[i] == 39 || data->parser.std_in[i] == 34)
			i = skip_to_next_quote(data, i);
		if (i == -1)
			return ;
		if (data->parser.std_in[i] == ' ')
		{
			data->elems++;
			while (data->parser.std_in[i] == ' ')
				i++;
		}
		else
			i++;
	}
	data->elems++;
	splitter2(data, data->elems);
}
*/
// /*
int	quotes_closed(char *cmd)
{
	int	inside;
	int	i;

	i = 0;
	inside = NO_Q;
	while (cmd && cmd[i])
	{
		quote_interpret(cmd[i], &inside);
		i++;
	}
	return (inside == NO_Q);
}

void	splitter(t_gen *data)
{
	if (!quotes_closed(data->parser.std_in))
		error(data, QUOTES_UNCLOSED);
	else
	{
		data->parser.parsed = split_w(ft_strtrim(data->parser.std_in, " "));
		if (!data->parser.parsed)
			error(data, BAD_MALLOC);
	}
}
// */
