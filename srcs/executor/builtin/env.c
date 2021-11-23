/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 19:51:40 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Prompt l'environnement
*/
int	ft_env(t_gen *data, char *pref, t_tree *ast)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		ft_putstr_fd(pref, ast->fd_out);
		ft_putstr_fd(tmp->name, ast->fd_out);
		ft_putstr_fd("=", ast->fd_out);
		ft_putstr_fd(tmp->content, ast->fd_out);
		ft_putstr_fd("\n", ast->fd_out);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
