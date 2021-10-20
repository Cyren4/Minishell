/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/19 18:01:15 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Prompt l'environnement
*/
int	ft_exit(t_gen *data, t_lexer *cmd)
{
	(void)cmd;
	data->status = 0;
	printf("exit\n");
	// if (cmd != NULL)
		// data->exit_stat = ft_atoi(cmd->content);
	return (EXIT_SUCCESS);
}
