/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:36:29 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 16:46:07 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_word(char *cmd)
{
	int	inside;
	int	i;
	int	count;

	i = 0;
	count = 0;
	inside = NO_Q;
	while (cmd && cmd[i])
	{
		while (cmd && cmd[i])
		{
			if ((cmd[i] == '"' && inside != SIMPLE_Q)
			|| (cmd[i] == '\'' && inside != DOUBLE_Q))
				quote_interpretation(cmd[i], &inside);
			if (cmd[i] == ' ' && inside == NO_Q)
				break ;
			i++;
		}
		count++;
		while (cmd && cmd[i] && cmd[i] == ' ')
			i++;
	}
	return (count);
}
// sub_word = start, len, num mot
char	**split_w(char *cmd)
{
	char	**ret;
	int		inside;
	int		sub_word[3];
	int		i;

	i = 0;
	sub_word[2] = 0;
	inside = NO_Q;
	ret = malloc(sizeof(char *) * (nb_word(cmd) + 1));
	if (!ret)
		return (NULL);
	while (cmd && cmd[i])
	{
		sub_word[0] = i;
		sub_word[1] = 0;
		while (cmd && cmd[i + sub_word[1]])
		{
			if ((cmd[i + sub_word[1]] == '"' && inside != SIMPLE_Q)
			|| (cmd[i + sub_word[1]] == '\'' && inside != DOUBLE_Q))
				quote_interpretation(cmd[i + sub_word[1]], &inside);
			if (cmd[i + sub_word[1]] == ' ' && inside == NO_Q)
				break ;
			sub_word[1]++;
		}
		ret[sub_word[2]] = ft_substr(cmd, sub_word[0], sub_word[1]);
		sub_word[2]++;
		i += sub_word[1];
		while (cmd && cmd[i] == ' ')
			i++;
	}
	ret[sub_word[2]] = NULL; 
	free(cmd);
	return (ret);
}

//dup sans caracter 
char	*strdup_sin_quote(char *s1)
{
	int		inside;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	inside = NO_Q;
	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		if ((s1[i] == '"' && inside != SIMPLE_Q)
			|| (s1[i] == '\'' && inside != DOUBLE_Q))
			quote_interpretation(s1[i], &inside);
		else
		{
			str[j] = s1[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

t_lexer	*get_words(t_lexer *head)
{
	char	**tmp;
	t_lexer	*new;
	t_lexer	*tmp_new;
	int		i;

	if (is_empty(head->content) == 1 || head->token != WORD)
		return (head);
	i = 1;
	tmp = split_w(ft_strtrim(head->content, " "));
	if (tmp == NULL)
		return (NULL);
	tmp_new = head;
	free(head->content);
	head->content = strdup_sin_quote(tmp[0]);
	while (tmp[i] != NULL)
	{
		new = malloc(sizeof(t_lexer));
		new->token = WORD;
		new->content = ft_strdup(tmp[i]);
		new->content = strdup_sin_quote(tmp[i]);
		new->next = NULL;
		tmp_new->next = new;
		tmp_new = tmp_new->next;
		i++;
	}
	free_tab(tmp);
	return (head);
}
