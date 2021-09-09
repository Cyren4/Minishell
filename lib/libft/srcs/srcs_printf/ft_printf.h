/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 00:46:20 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:24:29 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../../libft.h"

typedef struct s_flags
{
	int		len;
	int		dash;
	int		zero;
	int		width;
	int		precision;
	char	conversion;
	int		sign;
	int		c_z;
	int		plus;
	int		hash;
	int		space;
	int		r_sign;
}					t_flags;

int					ft_printf(char *format, ...
						)__attribute__((__format__(__printf__, 1, 2)));

void				init_flags(t_flags *flags);
int					check_conversion(char c);

void				conversion(va_list args, t_flags *flags);
void				go_in(char *format, va_list args, t_flags *flags);

char				*parse(char *format, va_list args, t_flags *flags);

void				display_char(int c, t_flags *flags);
void				display_string(char *str, t_flags *flags);
char				*add_zero(char *print, t_flags *flags);
void				display_nb(int nb, t_flags *flags);
void				display_uint(t_flags *flags, char *print);
void				convert_disp_uint(unsigned long int nb, t_flags *flags);
void				display_p(void *ptr, t_flags *flags);
void				display_ptr(t_flags *flags, char *print);

void				add_front(char *print, int c, int new_len, t_flags flags);
void				add_back(char *print, int c, int new_len, t_flags flags);
void				end_disp(char *print, t_flags *flags);

char				*convert_x(unsigned long int nb, char *base);

#endif
