/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:56:48 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:26:41 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	neg;

	i = 0;
	nbr = 0;
	neg = 1;
	while (str[i] && ((str[i] >= 8 && str[i] <= 13)
			|| str[i] == 32))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (neg * nbr);
}
