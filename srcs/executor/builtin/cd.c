/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:22 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/05 17:27:44 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	no_arg_cd(t_gen *data)
{
	t_env	*home;

	home = get_var_exist(data, "HOME");
	if (home == NULL)
		printf("cd: HOME not set\n");
	else
		return (home);	
}

void	ft_cd(t_gen *data, t_lexer *dir)
{
	char	*cur_path;

	if (dir == NULL)
	{
		cur_path = get_var_exist(data, "HOME");
		if (cur_path == NULL)
		{
			printf("cd: HOME not set\n");
			data->exit_stat = 1;
		}
	}
		no_arg_cd(data);
	else if (dir->content[0] == '/')
	{

	}
	else if (dir->content[0] == '.')

	// char	relative_path[256];
	// char	*abs_path;
	// int		ret;

	// // if (path[0] != '/')
    // {
	// 	if (!getcwd(relative_path, sizeof(relative_path)))
	// 		return (-1);
	// 	abs_path = join_char(relative_path, path, '/');
	// 	if (!abs_path)
	// 		return (-1);
	// 	ret = chdir(abs_path);
	// 	free(abs_path);
    // }
    // else
	// 	ret = chdir(path);
	// return (ret);
}