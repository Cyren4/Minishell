/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:05:46 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:31:49 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*src1;
	unsigned char	*dst1;
	size_t			i;

	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}
