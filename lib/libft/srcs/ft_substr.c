/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:54:40 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:34:26 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[start + i] && i < (unsigned int)len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
