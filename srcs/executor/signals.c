/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:11:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/19 17:58:30 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void exit_shell(int sig)
// {
// 	(void)sig;
// 	exit(1);
// }

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)sig;
	if (info->si_pid != 0)
		return ;
	printf("\n");//action when signal from child process
	display_prompt(get_data(NULL));
	// if (sig == SIGINT)
	// {
	// 	printf("\n");
	// minishell_loop(get_data(NULL));
	// }
	// printf("works\n");
}

void	receiveSIG(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
