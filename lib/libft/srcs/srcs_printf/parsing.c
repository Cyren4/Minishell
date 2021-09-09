/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 11:48:04 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/17 17:06:47 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X'
		|| c == '%')
		return (1);
	else
		return (0);
}

static char	*check_flags(char *format, t_flags *flags)
{
	while (*format == '-' || *format == '0' || *format == '#'
		|| *format == ' ' || *format == '+')
	{
		if (*format == '-')
		{
			flags->dash = 1;
			flags->zero = 0;
		}
		else if (*format == '0' && flags->dash == 0)
			flags->zero = 1;
		else if (*format == ' ')
			flags->space = 1;
		else if (*format == '#')
			flags->hash = 1;
		else if (*format == '+')
		{
			flags->plus = 1;
			flags->space = 0;
		}
		++format;
	}
	return (format);
}

static char	*check_width(char *format, va_list args, t_flags *flags)
{
	if (*format == '*')
	{
		flags->width = va_arg(args, int);
		format++;
	}
	else if (ft_isdigit(*format) == 1 || *format == '-')
	{
		flags->width = ft_atoi(format);
		while (ft_isdigit(*format) || *format == '-')
			++format;
	}
	if (flags->width < 0)
	{
		flags->dash = 1;
		flags->width = -flags->width;
	}
	return (format);
}

static char	*check_prec_conv(char *format, va_list args, t_flags *flags)
{
	if (*format == '.')
	{
		format++;
		flags->precision++;
		if (*format == '*')
		{
			flags->precision = va_arg(args, int);
			if (flags->precision < 0)
				flags->precision = -1;
			format++;
		}
		else if (ft_isdigit(*format))
		{
			flags->precision = ft_atoi(format);
			while (ft_isdigit(*format))
				++format;
		}
	}
	if (check_conversion(*format))
		flags->conversion = *format;
	return (format + 1);
}

char	*parse(char *format, va_list args, t_flags *flags)
{
	format = check_flags(format, flags);
	format = check_width(format, args, flags);
	format = check_prec_conv(format, args, flags);
	conversion(args, flags);
	return (format);
}
