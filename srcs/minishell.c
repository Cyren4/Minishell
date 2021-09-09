/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/09 17:26:33 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char **av, char **env)
{
	t_general mini;

	(void)av;
	(void)env;
	if (ac > 1)
		error(&mini, 1);
	set_vars(&mini);
	while (1)
	{
		if (mini.show_prompt == 1)
			display_prompt(&mini);
	}
	return(0);
}