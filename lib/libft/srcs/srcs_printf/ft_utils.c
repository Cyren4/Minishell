/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:46:04 by cramdani          #+#    #+#             */
/*   Updated: 2021/06/17 17:05:49 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_back(char *print, int c, int new_len, t_flags flags)
{
	int	len;

	len = ft_strlen(print) + flags.c_z;
	print = ft_memmove(print + new_len - len, print, len + 1);
	print -= (new_len - len);
	if (flags.sign == 1 && c == '0')
		ft_memset(print, c, new_len - len + 1);
	else
		ft_memset(print, c, new_len - len);
	*(print + new_len) = '\0';
}

void	add_front(char *print, int c, int new_len, t_flags flags)
{
	int	len;

	len = ft_strlen(print) + flags.c_z;
	ft_memset(print + len, c, new_len - len);
	*(print + new_len) = '\0';
}

char	*add_zero(char *print, t_flags *flags)
{
	int	len;

	len = ft_strlen(print);
	print = \
	ft_memmove(print + flags->precision - len + flags->sign, print, len);
	print -= (flags->precision - len + flags->sign);
	ft_memset(print, '0', flags->precision - len + 2 * flags->sign);
	if (flags->sign == 1)
		print[0] = '-';
	*(print + flags->precision + flags->sign) = '\0';
	return (print);
}

void	end_disp(char *print, t_flags *flags)
{
	int	len;

	if (flags->dash == 1)
		len = ft_strlen(print + flags->c_z) + flags->c_z;
	else
		len = ft_strlen(print) + flags->c_z;
	write(1, print, len);
	flags->len += len;
	free(print);
}
