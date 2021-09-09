/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:28:10 by cyrena            #+#    #+#             */
/*   Updated: 2021/08/13 01:32:33 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr || new_size < 1)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(sizeof(*ptr) * new_size));
	new_ptr = malloc(sizeof(*ptr) * new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
