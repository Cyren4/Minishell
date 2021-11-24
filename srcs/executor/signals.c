/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/24 14:56:35 by cramdani         ###   ########.fr       */
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

void	sig_int_child(int sig)
{
	get_exit_stat(128 + sig);
	rl_replace_line("", 1);
	rl_on_new_line();
	printf("\n");
}

void	sig_quit_child(int sig)
{
	get_exit_stat(128 + sig);
	if (get_pid(-1) == 0)
	{
		kill(get_pid(-1), SIGKILL);
		printf("Quit (core dumped)\n");
	}
}

void	sig_int(int sig)
{
	(void)sig;

	get_exit_stat(130);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_child(void)
{
	signal(SIGTERM, print_mes);
	signal(SIGSEGV, print_mes);
	signal(SIGBUS, print_mes);
	signal(SIGABRT, print_mes);
	signal(SIGINT, sig_int_child);
	signal(SIGQUIT, SIG_IGN);
}

void	receiveSIG(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
