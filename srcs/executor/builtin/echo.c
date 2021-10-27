/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/21 12:07:38 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	joins 2 lines with the separator sep in between
*/
char	*join_sep(char *s1, char *s2, char sep)
{
	size_t	len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	str = NULL;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (i != 0)
		str[i++] = sep;
	while (s2 && s2[++j])
		str[i + j] = s2[j];
	str[i + j] = 0;
	if (s1)
		free(s1);
	return (str);
}

int	ft_echo(t_lexer *lex)
{
	t_lexer	*tmp;
	char	*print;
	int		opt;

	opt = 0;
	tmp = lex;
	if (tmp && ft_strcmp(tmp->content, "-n") == 0)
	{
		opt = 1;
		tmp = tmp->next;
	}
	print = NULL;
	while (tmp)
	{
		if (print || tmp->content)
			print = join_sep(print, tmp->content, ' ');
		tmp = tmp->next;
	}
	if (print != NULL)
	{
		printf("%s", print);
		free(print);
	}
	if (opt == 0)
		printf("\n");
	return (1);
}
