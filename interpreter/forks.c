/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:22:39 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/30 15:34:03 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	char *std_in;
	int fd_in;

	dup2(STDIN_FILENO, fd_in);

	while (1)
	{
		std_in = readline("input here: ");
		lstat()
		ft_putstr_fd(std_in, fd_in);
	}
	return(0);
}