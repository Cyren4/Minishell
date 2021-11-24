/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:08:52 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 21:05:54 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**splitting(char *cmd, int *vect, int nb_words)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (nb_words + 1));
	if (!ret)
		return (NULL);
	while (i < nb_words)
	{
		if (i == nb_words - 1)
			ret[i] = ft_substr(cmd, vect[i], ft_strlen(cmd) - vect[i]);
		else
			ret[i] = ft_substr(cmd, vect[i], vect[i + 1] - vect[i]);
		i++;
	}
	ret[i] = NULL;
	free(vect);
	return (ret);
}

int	is_special(char *cmd)
{
	if (ft_strncmp(cmd, "<<", 2) == 0 || ft_strncmp(cmd, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(cmd, "|", 1) == 0 || ft_strncmp(cmd, "<", 1) == 0
		|| ft_strncmp(cmd, ">", 1) == 0)
		return (1);
	return (0);
}

void	norm_subwords(char *cmd, int *vect, int *i, int *i_word)
{
	if (*i != 0)
		vect[++*i_word] = *i;
	*i += is_special(cmd + *i);
	if (cmd[*i] && !is_special(cmd + *i))
		vect[++*i_word] = *i;
	*i -= 1;
}

char	**check_sub_words(char *cmd)
{
	int	*vect;
	int	i;
	int	i_word;
	int	inside;

	i = 0;
	vect = malloc(sizeof(int) * (ft_strlen(cmd) + 1));
	if (!vect)
		return (NULL);
	i_word = 0;
	vect[i_word] = 0;
	inside = NO_Q;
	while (cmd[i])
	{
		if (need_interpret_quote(cmd[i], inside))
			quote_interpretation(cmd[i], &inside);
		else if (inside == NO_Q && is_special(cmd + i))
			norm_subwords(cmd, vect, &i, &i_word);
		i++;
	}
	return (splitting(cmd, vect, i_word + 1));
}
