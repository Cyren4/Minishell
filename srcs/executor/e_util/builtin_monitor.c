/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:20:27 by cramdani          #+#    #+#             */
/*   Updated: 2021/08/09 01:15:00 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i] && s2[i] && *s1 == *s2 )
			i++;
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (0);
}


int exec_builtin(char *cmd, t_data *data)
{
    int ret;
    
    if (ft_strcmp(cmd, "echo") == 0)
        ret = ft_echo(data);
    else if (ft_strcmp(cmd, "cd") == 0)
        ret = ft_cd(data);
    else if (ft_strcmp(cmd, "pwd") == 0)
        ret = ft_pwd(data);
    else if (ft_strcmp(cmd, "export") == 0)
        ret = ft_cd(data);
    else if (ft_strcmp(cmd, "unset") == 0)
        ret = ft_unset(data);
    else if (ft_strcmp(cmd, "env") == 0)
        ret = ft_env(data);
    else if (ft_strcmp(cmd, "exit") == 0)
        ret = ft_exit(data);
    return (ret);
}