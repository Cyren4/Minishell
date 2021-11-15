/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:00:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/14 18:08:15 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to delete
void	display_array(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		printf("array[%i]: %s\n", i, path[i]);
		i++;
	}
}

//to delete once done
void	display_token(t_lexer *lst_lex)
{
	t_lexer	*tmp;
	char	*token[8] = {"PIPE", "LT", "LT2", "GT", "GT2", "CMD", "OPTION", "WORD"};

	printf("Let's show token\n");
	tmp = lst_lex;
	if (!lst_lex)
	{
		printf("Empty\n");
		return ;
	}
	while (tmp)
	{
		printf("%s\t%s\n", tmp->content, token[tmp->token]);
		tmp = tmp->next;
	}
}
//cd.c
// if (ft_strcmp(dir->content, "~") == 0 || ft_strncmp(dir->content, "~/", 2) == 0)
// dir->content = replace_home(data, dir);

// char	*replace_home(t_gen *data, t_lexer *dir)
// {
// 	char	*home;
// 	home = NULL;
// 	if (ft_strcmp(dir->content, "~") == 0)
// 		home = ft_strdup(data->home);
// 	else
// 	{
// 		home = ft_substr(dir->content, 1, ft_strlen(dir->content) - 1);
// 		home = ft_strjoin(data->home, home);
// 	}
// 	free(dir->content);
// 	dir->content = NULL;
// 	return (home);
// }
