/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 02:04:50 by cyrena            #+#    #+#             */
/*   Updated: 2021/08/13 01:35:19 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	in(char c, char *base)
{
	while (*base)
	{
		if (*base == c)
			return (1);
		base++;
	}
	return (0);
}

int	check_nb_in_base(char *str, char *base)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in(str[i], base) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	res;
	int	size_base;
	int	i;
	int	j;

	if (!str || !base || check_base(base) == 0
		|| check_nb_in_base(str, base) == 0)
		return (-1);
	res = 0;
	i = 0;
	size_base = ft_strlen(base);
	while (str[i])
	{
		j = 0;
		while (str[i] != base[j])
			j++;
		res += puissance(size_base, ft_strlen(str) - i - 1) * j;
		i++;
	}
	return (res);
}
