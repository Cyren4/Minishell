/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 21:24:22 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:35:27 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;

	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	return (ft_memset(mem, 0, size * count));
}
