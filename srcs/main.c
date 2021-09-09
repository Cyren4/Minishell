/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:17:21 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/09 17:25:03 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		printf("Error : No arguments expected\n");
		printf("Usage : %s\n", av[0]);
		return (1);
	}
	minishell(env);
	return (0);
}