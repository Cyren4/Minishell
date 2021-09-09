/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:45:38 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/27 19:06:38 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs_printf/ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->dash = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->sign = 0;
	flags->conversion = '0';
	flags->c_z = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->r_sign = 0;
}

int	ft_printf(char *format, ...)
{
	va_list	args;
	t_flags	flags;

	flags.len = 0;
	if (!format)
		return (0);
	va_start(args, format);
	go_in(format, args, &flags);
	va_end(args);
	return (flags.len);
}
