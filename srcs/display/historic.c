/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 20:12:43 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/26 20:20:04 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_historic(char *line, t_gen *data)
{
	t_hist	*new;

	new = malloc(sizeof(t_hist));
	new->past = NULL;
	new->line = ft_strdup(line);
	new->next = data->hist;
	data->hist = new;
}

int	is_empty(char *line, t_gen *data)
{
	int	i;

	i = 0;
	if (line || ft_strcmp(data->hist->line, line) == 0)
		return (1);
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
}