/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/27 21:58:57 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void exit_shell(int sig)
// {
// 	(void)sig;
// 	exit(1);
// }

void	sig_int(int sig)
{
	(void)sig;

	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit(int sig)
{
	(void)sig;
	printf("\b\b  \b\b");
}

void	receiveSIG(void)
{
	// struct sigaction	sa;
	// struct sigaction	sb;

	// sa.sa_flags = SA_SIGINFO;
	// sa.sa_sigaction = s_int;
	// sb.sa_flags = SA_SIGINFO;
	// sb.sa_sigaction = s_quit;
	// sigaction(SIGINT, NULL, &sa);
	// sigaction(SIGQUIT, &sb, NULL);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
