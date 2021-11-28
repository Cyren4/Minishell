/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:39:21 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/28 14:36:23 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	len_int(int nb)
{
	int	i;
	int	tmp;

	i = 0;
	if (nb == 0)
		return (1);
	tmp = nb;
	if (nb < 0)
		tmp = -nb;
	while (tmp > 0)
	{
		i++;
		tmp = tmp / 10;
	}
	return (i);
}

//return la nbOccur occurence de c dans str
//-1 si elle n'existe pas
int	occur(char *str, char c, int nbOccur)
{
	int	i;
	int	occur;

	i = 0;
	occur = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			occur++;
		if (occur == nbOccur)
			return (i);
		i++;
	}
	return (-1);
}

int	in(char c, char *sin)
{
	int	i;

	i = 0;
	while (sin && sin[i])
	{
		if (sin[i] == c)
			return (1);
		i++;
	}
	return (0);
}
