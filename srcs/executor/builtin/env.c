/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/27 15:29:30 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Prompt l'environnement
*/
int	ft_env(t_gen *data, char *pref, t_lexer *cmd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		printf("%s%s=%s\n", pref, tmp->name, tmp->content);
		tmp = tmp->next;
	}
	if (cmd != NULL)
		print_error("minishell: env: ", "too many arguments\n", NULL);
	return (EXIT_SUCCESS);
}
