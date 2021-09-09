/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 19:01:48 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/25 16:30:23 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	uint_len(unsigned long int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += 1;
	while (n != 0)
	{
		n = n / 10;
		size += 1;
	}
	return (size);
}

static char	*u_itoa(unsigned long int nbr)
{
	char	*str;
	int		len;

	len = uint_len(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len > 0)
	{
		str[--len] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (str);
}

static int	check_s(unsigned long int nb, int size)
{
	int	i;

	i = 0;
	while (nb >= (unsigned long int)size)
	{
		nb = nb / size;
		i++;
	}
	i++;
	return (i);
}

char	*convert_x(unsigned long int nb, char *base)
{
	int		i;
	char	*nb_base;

	i = check_s(nb, 16);
	nb_base = malloc(sizeof(char) * (i + 1));
	if (!nb_base)
		return (NULL);
	nb_base[i] = '\0';
	while (nb >= 16 && i >= 0)
	{
		i--;
		nb_base[i] = base[nb % 16];
		nb = nb / 16;
	}
	nb_base[--i] = base[nb % 16];
	return (nb_base);
}

void	convert_disp_uint(unsigned long int nb, t_flags *flags)
{
	char	*print;

	if (nb == 0 && flags->precision == 0)
		print = ft_strdup("");
	else if (flags->conversion == 'u')
		print = u_itoa(nb);
	else if (flags->conversion == 'x' || flags->conversion == 'p')
		print = convert_x(nb, "0123456789abcdef");
	else if (flags->conversion == 'X')
		print = convert_x(nb, "0123456789ABCDEF");
	if (flags->conversion == 'p')
		display_ptr(flags, print);
	else
		display_uint(flags, print);
}
