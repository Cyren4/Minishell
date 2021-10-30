/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:06:23 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/30 15:16:39 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env_vars(t_env *envs)
{
	t_env	*head;

	head = envs;
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->content);
		envs = envs->next;
	}
	envs = head;
}
