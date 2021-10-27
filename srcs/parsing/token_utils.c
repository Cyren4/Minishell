/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:28:48 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/27 16:37:52 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	quote_interpretation(char quote, int *inside)
{
	if (quote == '"' && *inside == NO_Q)
		*inside = DOUBLE_Q;
	else if (quote == '\'' && *inside == NO_Q)
		*inside = SIMPLE_Q;
	else if (quote == '\'' && *inside == SIMPLE_Q)
		*inside = NO_Q;
	else if (quote == '"' && *inside == DOUBLE_Q)
		*inside = NO_Q;
}

//to delete once done
void	display_token(t_lexer *lst_lex)
{
	t_lexer	*tmp;
	char	*token[8] = {"PIPE", "LT", "LT2", "GT", "GT2", "CMD", "OPTION", "WORD"};
	
	printf("Let's show token\n");
	tmp = lst_lex;
	if(!lst_lex)
	{
		printf("Empty\n");
		return;
	}
	while (tmp)
	{
		printf("%s\t%s\n", tmp->content, token[tmp->token]);
		printf("%s\n", tmp->hdoc_content);
		tmp = tmp->next;
	}
}
