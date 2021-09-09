/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 01:01:14 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/25 16:29:51 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	display_char(int c, t_flags *flags)
{
	char	*print;

	print = malloc(sizeof(char) * 2);
	if (!print)
		return ;
	*print = (unsigned char)c;
	*(print + 1) = '\0';
	if (c == '\0')
		flags->c_z = 1;
	if (flags->width > 1)
	{
		print = ft_realloc(print, (flags->width + 1));
		if (flags->dash == 1)
			add_front(print, ' ', flags->width, *flags);
		else if (flags->zero == 1)
			add_back(print, '0', flags->width, *flags);
		else
			add_back(print, ' ', flags->width, *flags);
		*(print + flags->width) = '\0';
	}
	end_disp(print, flags);
}

void	display_string(char *str, t_flags *flags)
{
	char	*print;

	if (!str)
		str = ft_strdup("(null)");
	if (flags->precision < (int)ft_strlen(str))
		print = ft_substr(str, 0, flags->precision);
	else
		print = ft_strdup(str);
	if (flags->width > (int)ft_strlen(print))
	{
		print = ft_realloc(print, (flags->width + 1));
		if (flags->dash == 1)
			add_front(print, ' ', flags->width, *flags);
		else if (flags->zero == 1 && flags->precision == -1)
			add_back(print, '0', flags->width, *flags);
		else
			add_back(print, ' ', flags->width, *flags);
	}
	end_disp(print, flags);
}
