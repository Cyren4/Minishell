/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/04 18:14:18 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	If n is specified, but its value is not between 0
	and 255 inclusively, the exit status is undefined.
*/
int	exit_atoi(char *str)
{
	int			i;
	long long	ret;
	long long	neg;
	char		*tmp;

	tmp = ft_strtrim(str, " ");
	i = tmp[0] == '-' || tmp[0] == '+';
	ret = 0;
	neg = 1;
	while (str && ft_isspace(tmp[i]))
		i++;
	if (tmp[0] == '-')
		neg = -1;
	while (tmp[i] && tmp[i] >= '0' && tmp[i] <= '9')
	{
		ret = ret * 10 + tmp[i] - '0';
		i++;
	}
	ret = ret * neg;
	free(tmp);
	return (ret % 256);
}

int	exit_isnumber(char	*nb)
{
	char	*tmp;
	int		ret;

	tmp = ft_strtrim(nb, " ");
	if (tmp[0] == '-' || tmp[0] == '+')
		ret = ft_isnumber(tmp + 1);
	else
		ret = ft_isnumber(tmp);
	if (ret && (ft_strlen(tmp) > 20))
		ret = 0;
	free(tmp);
	return (ret);
}

int	ft_exit(t_gen *data, t_lexer *cmd)
{
	int	is_num;

	printf("exit\n");
	if (cmd)
	{
		is_num = exit_isnumber(cmd->content);
		if (is_num && cmd->next != NULL)
		{
			print_error("exit: too many arguments\n", NULL, NULL);
			return (1);
		}
		else if (!is_num)
		{
			print_error("exit: ", cmd->content, ": numeric argument required\n");
			data->exit_stat = 255;
		}
		else if (cmd->next != NULL)
		{
			print_error("exit: too many arguments\n", NULL, NULL);
			data->exit_stat = 1;
		}
		else
			data->exit_stat = exit_atoi(cmd->content);
	}
	exit(data->exit_stat);
}
	// printf("%d\n", data->exit_stat);
	// clean_data(data);
	// delete_data(data);
