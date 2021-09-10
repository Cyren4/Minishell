/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:22 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/09 12:20:17 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	*join_char(char *s1, char *s2, char c)
{
	int		length;
	char	*result;

	if (!(s1) || !(s2))
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc((sizeof(char)) * (length + 1));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[ft_strlen(s1)] = c;
	result[ft_strlen(s1) + 1] = '\0';
	ft_strcat(result, s2);
	return (result);
}


int cd(char *path)
{
	char	relative_path[256];
	char	*abs_path;
	int		ret;

	if (path[0] != '/')
    {
		if (!getcwd(relative_path, sizeof(relative_path)))
			return (-1);
		abs_path = join_char(relative_path, path, '/');
		if (!abs_path)
			return (-1);
		ret = chdir(abs_path);
		free(abs_path);
    }
    else
		ret = chdir(path);
	return (ret);
}