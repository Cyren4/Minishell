/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:31:39 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/17 17:27:38 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//	if (nb < 0 || (nb == 0 && flags->precision == 0 && 
// (flags->plus == 1 || flags->space == 1))
static char	*check_nb(int nb, t_flags *flags)
{
	if (nb < 0 || (nb == 0 && flags->plus + flags->space >= 1))
		flags->sign = 1;
	if (flags->precision == 0 && nb == 0)
	{
		if (flags->plus)
			return (ft_strdup("+"));
		else if (flags->space)
			return (ft_strdup(" "));
		else
			return (ft_strdup(""));
	}
	else if (nb == 0 && (flags->plus == 1 || flags->space == 1))
		return (ft_itoa(-1));
	else if (flags->plus == 1 || flags->space == 1)
	{
		flags->r_sign = flags->sign;
		flags->sign = 1;
		if (nb < 0)
			return (ft_itoa(nb));
		else
			return (ft_itoa(-nb));
	}
	return (ft_itoa(nb));
}

static void	min_flags(char *print, t_flags *flags, int nb)
{
	char	c;
	int		i;

	i = 0;
	c = ' ';
	if (flags->plus == 1)
		c = '+';
	if ((flags->plus == 0 && flags->space == 0) || flags->r_sign == 1)
		return ;
	else if (flags->precision == 0 && nb == 0)
	{
		if (flags->dash)
			print[0] = c;
		else
			print[ft_strlen(print) - 1] = c;
		return ;
	}
	while (print[i] && print[i] != '-')
		++i;
	print[i] = c;
	if (!(nb == 0 && (flags->plus == 1 || flags->space == 1)))
		return ;
	while (*print && *print != '1')
		++print;
	*print = '0';
}

void	display_nb(int nb, t_flags *flags)
{
	char	*print;
	int		len;

	print = check_nb(nb, flags);
	len = ft_strlen(print);
	if (flags->precision > len - flags->sign)
	{
		print = realloc(print, flags->precision + flags->sign + 1);
		print = add_zero(print, flags);
	}
	len = ft_strlen(print);
	if (flags->width > len)
	{
		print = ft_realloc(print, flags->width + 1);
		if (flags->dash == 1)
			add_front(print, ' ', flags->width, *flags);
		else if (flags->zero == 1 && flags->precision == -1)
			add_back(print, '0', flags->width, *flags);
		else
			add_back(print, ' ', flags->width, *flags);
		if (flags->sign == 1 && (flags->zero == 1 && flags->precision == -1))
			print[0] = '-';
	}
	min_flags(print, flags, nb);
	end_disp(print, flags);
}
