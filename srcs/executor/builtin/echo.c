/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/14 19:07:01 by cramdani         ###   ########.fr       */
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

t_lexer	*check_option(t_lexer *lex, int *opt)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	*opt = 0;
	while (tmp && tmp->content[0] == '-')
	{
		i = 1;
		while (tmp->content[i])
		{
			if (tmp->content[i] != 'n')
				break ;
			i++;
		}
		if (tmp->content[i] != '\0')
			break ;
		*opt = 1;
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_echo(t_lexer *lex, t_tree *ast)
{
	t_lexer	*tmp;
	char	*print;
	int		opt;

	tmp = check_option(lex, &opt);
	print = NULL;
	while (tmp)
	{
		if (print || tmp->content)
			print = join_sep(print, tmp->content, ' ');
		tmp = tmp->next;
	}
	if (print != NULL)
	{
		ft_putstr_fd(print, ast->fd_out);
		free(print);
	}
	if (opt == 0)
		ft_putstr_fd("\n", ast->fd_out);
	return (EXIT_SUCCESS);
}
