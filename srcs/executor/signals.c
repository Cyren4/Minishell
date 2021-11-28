/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/26 22:48:55 by vbaron           ###   ########.fr       */
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
	get_exit_stat(128 + sig);
}

void	sig_int(int sig)
{
	(void)sig;
	get_exit_stat(130);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_child(void)
{
	signal(SIGTERM, print_mes);
	signal(SIGSEGV, print_mes);
	signal(SIGBUS, print_mes);
	signal(SIGABRT, print_mes);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	receive_sig(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
