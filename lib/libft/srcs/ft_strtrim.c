/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:30:27 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:34:21 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_unwanted(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_unwanted(s1[i], set))
		i++;
	return (i);
}

static size_t	check_size(char const *s1, char const *set)
{
	size_t	len;
	int		i;

	i = ft_strlen(s1) - 1;
	while (s1[i] && i >= 0 && is_unwanted(s1[i], set))
		i--;
	i++;
	if (i == 0)
		return (0);
	len = i - start(s1, set);
	return (len);
}

static int	all_set(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!(is_unwanted(s1[i], set)))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	if (all_set(s1, set))
		return (ft_strdup(""));
	len = check_size(s1, set);
	return (ft_substr(s1, (unsigned int)start(s1, set), len));
}
