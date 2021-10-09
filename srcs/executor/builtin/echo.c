/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/09 15:54:33 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_echo(t_lexer *lex)
{
	t_lexer *tmp;
	
	tmp = lex;
	while (tmp)
	{
		printf("%s");
		tmp = tmp->next;
	}
	if (lex->opt == 1)
		printf("\n");
	return (1);
}