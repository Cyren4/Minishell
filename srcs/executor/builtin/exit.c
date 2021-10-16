/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/10 13:14:03 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Prompt l'environnement
*/
int	ft_exit(t_gen *data, char *pref)
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
