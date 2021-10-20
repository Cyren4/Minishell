/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 12:57:36 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/20 17:02:22 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#define BUFFER_SIZE 1

char	*cur_line(char *old)
{
	int		i;
	char	*str;

	i = 0;
	while (old[i] && old[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (old[i] && old[i] != '\n')
	{
		str[i] = old[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*next_line(char *old)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (old[i] && old[i] != '\n')
		i++;
	if (!old[i])
	{
		free(old);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(old) - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (old[++i])
	{
		str[j] = old[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(old);
	return (str);
}

char	*new_join(char *old, char *buf)
{
	char	*new;

	new = ft_strjoin(old, buf);
	free(old);
	return (new);
}

int	get_next_line(int fd, char **line)
{
	static char	*old;
	char		buf[BUFFER_SIZE + 1];
	int			r;

	*buf = 0;
	r = 1;
	if (!line)
		return (-1);
	*line = NULL;
	while (buf[0] != '\n' && r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (-1);
		buf[r] = '\0';
		old = new_join(old, buf);
	}
	*line = cur_line(old);
	old = next_line(old);
	return (r != 0);
}
