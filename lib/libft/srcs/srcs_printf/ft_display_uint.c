/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 19:51:25 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/17 17:02:54 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	display_uint(t_flags *flags, char *print)
{
	int	len;

	len = ft_strlen(print);
	if (flags->precision > len)
	{
		print = realloc(print, flags->precision + 1);
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
	}
	end_disp(print, flags);
}

void	display_ptr(t_flags *flags, char *print)
{
	int	len;

	len = ft_strlen(print) + 2;
	print = realloc(print, len + 1);
	add_back(print, '0', len, *flags);
	print[1] = 'x';
	if (flags->width > len)
	{
		print = ft_realloc(print, flags->width + 1);
		if (flags->dash == 1)
			add_front(print, ' ', flags->width, *flags);
		else
			add_back(print, ' ', flags->width, *flags);
	}
	end_disp(print, flags);
}
