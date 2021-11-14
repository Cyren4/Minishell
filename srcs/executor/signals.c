/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/14 17:55:05 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_mes(int sig)
{
	if (sig == SIGTERM)
		printf("sigterm\n");
	else if (sig == SIGSEGV)
		printf("SIGSEGV\n");
	else if (sig == SIGBUS)
		printf("SIGBUS\n");
	else if (sig == SIGABRT)
		printf("SIGABRT\n");
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
