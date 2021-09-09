/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:50:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/09 18:07:31 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main()
{
	t_command cmd;

	cmd.echo.n = 0;
	cmd.echo.str = ft_substr("Hello World!", 0, ft_strlen("Hello World!"));
	ft_echo(&(cmd.echo));
	return(0);
}
