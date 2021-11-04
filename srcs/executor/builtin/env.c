/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/08 23:21:16 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Prompt l'environnement
*/
int	ft_env(t_gen *data, char *pref)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		printf("%s%s=%s\n", pref, tmp->name, tmp->content);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
