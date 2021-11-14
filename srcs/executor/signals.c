/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/14 18:45:50 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_mes(int sig)
{
	if (sig == SIGTERM)
		printf("Terminated\n");
	else if (sig == SIGSEGV)
		printf("Segmentation fault (core dumped)\n");
	else if (sig == SIGBUS)
		printf("Bus error (core dumped)\n");
	else if (sig == SIGABRT)
		printf("Aborted (core dumped)\n");
}

void	sig_child(void)
{
	signal(SIGTERM, print_mes);
	signal(SIGSEGV, print_mes);
	signal(SIGBUS, print_mes);
	signal(SIGABRT, print_mes);
}

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
	
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
