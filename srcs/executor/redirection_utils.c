/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:46:42 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/23 13:52:12 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid(char *cmd, int *cmd_i, t_gen *data)
{
	char	*env_var;
	int		i;
	char	*tmp;
	char	ret;

	i = 0;
	ret = 1;
	if (ft_strncmp(src + *cmd_i, "$?", 2) == 0)
		return (ret);
	env_var = malloc(sizeof(char *) * (ft_strlen(cmd) - *cmd_i + 1));
	if (!env_var)
		return (-1);
	*cmd_i += 1;
	while (cmd[*i] && (ft_isalnum(cmd[*cmd_i]) || cmd[*cmd_i] == '_'))
	{
		env_var[i] = cmd[*cmd_i];
		*src_i += 1;
		i++;
	}
	env_var[i] = '\0';
	tmp = get_env_var(data, env_var);
	i = -1;
	while (tmp[++i])
		if (ft_isspace(tmp[i])))
			ret = 0;
	ft_free(env_var);
	return (ret);
}

//retour 1 si il n'y a pas plusieurs mots 0 sinon 
int is_valid_redir(char *cmd, t_gen *data)
{
	char	*r_cont;
	int		i;
	int		in;

	i = 0;
	el_i = 0;
	valid = 1;
	in = NO_Q;
	while (cmd[i])
	{
		if ((cmd[i] == '"' && in != SIMPLE_Q)
			|| (cmd[i] == '\'' && in != DOUBLE_Q))
			quote_interpretation(cmd[i], &in);
		if (cmd[i] == '$' && in == NO_Q
			&& valid_e(elm->content, el_i))
		{
			if(!check_valid(cmd, &i, data))
				return (0);
			continue ;
		}
		i++;
	}
	return (1);
}
