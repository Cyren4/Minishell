/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 11:48:15 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/27 19:08:02 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	go_in(char *format, va_list args, t_flags *flags)
{
	int	i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			write(1, format, i);
			flags->len += i;
			init_flags(flags);
			format = parse(format + i + 1, args, flags);
			i = 0;
		}
		else
			i++;
	}
	write(1, format, i);
	flags->len += i;
}
