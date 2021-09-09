/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 02:05:16 by cyrena            #+#    #+#             */
/*   Updated: 2021/08/13 01:32:20 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i] != '\0')
	{
		j = i + 1;
		if (base[i] == '-' || base[i] == '+' || base[i] == ' '
			|| ft_isspace(base[i]) == 1)
			return (0);
		while (base[i] != '\0' && base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_size2(int nb, int size)
{
	int	i;

	i = 0;
	while (nb >= size)
	{
		nb = nb / size;
		i++;
	}
	i++;
	return (i);
}

void	ft_putnbr_base(int nb, char *base)
{
	int		base_size;
	int		i;
	char	*nb_base;

	base_size = ft_strlen(base);
	i = check_size2(nb, base_size);
	if (check_base(base) == 1)
	{
		nb_base = malloc(sizeof(char) * i);
		if (!nb_base)
			return ;
		nb_base[i] = 0;
		while (nb >= base_size)
		{
			i--;
			nb_base[i] = base[nb % base_size];
			nb = nb / base_size;
		}
		nb_base[--i] = base[nb % base_size];
		write(1, nb_base, ft_strlen(nb_base));
		free(nb_base);
	}
}
