/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:00:11 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/30 15:31:28 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
