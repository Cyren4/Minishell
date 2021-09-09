/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 02:05:06 by cyrena            #+#    #+#             */
/*   Updated: 2021/08/13 01:27:55 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*convert(int nb, char *base)
{
	int		base_size;
	int		i;
	char	*nb_base;

	base_size = ft_strlen(base);
	i = check_size2(nb, base_size);
	if (check_base(base) == 0)
		return (NULL);
	else
	{
		nb_base = malloc(sizeof(char) * i);
		if (!nb_base)
			return (NULL);
		nb_base[i] = 0;
		while (nb >= base_size)
		{
			i--;
			nb_base[i] = base[nb % base_size];
			nb = nb / base_size;
		}
		nb_base[--i] = base[nb % base_size];
	}
	return (nb_base);
}

char	*ft_convert_base(char *nb, char *base_from, char *base_to)
{
	char	*nb_base;
	int		nb_decimal;

	if (!check_base(base_from) || !check_base(base_to)
		|| !check_nb_in_base(nb, base_from))
		return (NULL);
	nb_decimal = ft_atoi_base(nb, base_from);
	nb_base = convert(nb_decimal, base_to);
	return (nb_base);
}
