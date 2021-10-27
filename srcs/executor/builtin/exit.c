/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/27 15:36:48 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	If n is specified, but its value is not between 0
	and 255 inclusively, the exit status is undefined.
*/
int	exit_atoi(char *str)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	if (!str || str[0] == '-' || ft_strlen(str) > 3)
		ret = 1;
	else
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			ret = ret * 10 + str[i] - '0';
			i++;
		}
	}
	return (ret % 256);
}

int	ft_exit(t_gen *data, t_lexer *cmd)
{
	int ret;
	t_lexer *tmp;

	tmp = cmd;
	ret = 0;
	printf("exit\n");
	if (tmp)
	{
		if (ft_isnumber(tmp->content) && cmd->next != NULL)
		{
			print_error("exit: too many arguments\n", NULL, NULL);
			clean_lex(data->lex);
			data->lex = NULL;
			return (1);
		}
		else if (!ft_isnumber(tmp->content) || cmd->next != NULL)
		{
			if (!ft_isnumber(tmp->content))
				print_error("exit: ", cmd->content, ": numeric argument required\n");
			else
				print_error("exit: too many arguments\n", NULL, NULL);
			ret = 255;
		}
		else
			ret = exit_atoi(cmd->content);
	}
	// clean_data(data);
	// delete_data(data);
	exit(ret);
}
