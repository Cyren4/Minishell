/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:22:37 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/26 15:53:58 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	If n is specified, but its value is not between 0
	and 255 inclusively, the exit status is undefined.
*/
long long	exit_atoi(char *str)
{
	int			i;
	long long	ret;
	long long	neg;
	char		*tmp;

	tmp = ft_strtrim(str, " ");
	i = is_sign(tmp[0]);
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
	return (ret);
}

int	is_long(char *nb, int i)
{
	char			*tmp;
	long long int	h_num;

	tmp = ft_substr(nb, i, 11);
	tmp[i + 11] = '\0';
	h_num = exit_atoi(tmp);
	tmp[i + 11] = '0';
	free(tmp);
	if (h_num == 92233720368)
	{
		tmp = ft_substr(nb, 11 + i, 10);
		h_num = exit_atoi(tmp);
		free(tmp);
		if ((nb[0] == '-' && h_num > 54775808)
			|| h_num > 54775807)
			return (0);
	}
	else if (h_num > 92233720368)
		return (0);
	return (1);
}

int	exit_isnumber(char	*nb)
{
	char	*tmp;
	int		ret;
	int		i;

	i = 0;
	tmp = ft_strtrim(nb, " ");
	if (tmp[0] == '-' || tmp[0] == '+')
		i = 1;
	ret = ft_isnumber(tmp + i);
	if (ret && (ft_strlen(tmp) + 1 > (size_t)(20 + i)))
		ret = 0;
	else if (ft_strlen(tmp) + 1 == (size_t)(20 + i))
	{
		ret = is_long(tmp, i);
	}
	free(tmp);
	return (ret);
}

void	norm_exit(int is_num, t_lexer *cmd)
{
	if (!is_num)
	{
		print_error("exit: ", cmd->content, ": numeric argument required\n");
		get_exit_stat(2);
	}
	else if (cmd->next != NULL)
	{
		print_error("exit: too many arguments\n", NULL, NULL);
		get_exit_stat(1);
	}
	else
		get_exit_stat(exit_atoi(cmd->content) % 256);
}

int	ft_exit(t_gen *data, t_lexer *cmd)
{
	int	is_num;

	(void)data;
	if (get_pid(-1) != 0)
		printf("exit\n");
	if (cmd)
	{
		is_num = exit_isnumber(cmd->content);
		if (is_num && cmd->next != NULL)
		{
			print_error("exit: too many arguments\n", NULL, NULL);
			return (get_exit_stat(1));
		}
		else
			norm_exit(is_num, cmd);
	}
	if (get_pid(-1) != 0)
		clean_exit(data);
	if (get_pid(-1) == 0)
		return (get_exit_stat(-1));
	exit(get_exit_stat(-1));
}
