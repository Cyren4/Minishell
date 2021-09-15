/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:06:23 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/15 19:19:32 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void display_env_vars(t_env *envs)
{
	t_env *head;

	head = envs;
	
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->content);
		envs = envs->next;
	}
	envs = head;
}