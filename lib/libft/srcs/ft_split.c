/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:37:28 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/13 01:32:37 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	nb_w(char const *s, char c)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (-1);
	i = -1;
	len = 1;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[++i])
	{
		if (s[i] == c)
			len++;
		while (s[i] == c && s[i])
			i++;
	}
	return (len);
}

static size_t	check_len(char const *s, char c, size_t start)
{
	size_t	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
	{
		len++;
	}
	return (len);
}

static void	*clear(char **strs, char *str)
{
	int	i;

	i = 0;
	free(str);
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	return (NULL);
}

char	*c_trim(const char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strtrim(s, tmp));
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*str;
	size_t	j;
	size_t	i;
	size_t	len;

	str = c_trim(s, c);
	j = -1;
	i = 0;
	strs = malloc(sizeof(char *) * (nb_w(str, c) + 1));
	if (!str || !strs)
		return (NULL);
	while (++j < nb_w(str, c))
	{
		len = check_len(str, c, i);
		strs[j] = ft_substr(str, i, len);
		if (!strs)
			return (clear(strs, str));
		i = i + len;
		while (str[i] == c && str[i])
			i++;
	}
	strs[j] = NULL;
	free((void *)str);
	return (strs);
}
