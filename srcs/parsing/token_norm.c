/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:00:28 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 21:04:58 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check si expansion valide 
//(soit $? ou au moins lettre/_)
int	valid_e(char *content, int index)
{
	return (ft_isalpha(content[index + 1])
		|| content[index + 1] == '_'
		|| content[index + 1] == '\"'
		|| content[index + 1] == '\''
		|| content[index + 1] == '?');
}

int	need_interpret_quote(char c, int inside)
{
	return ((c == '"' && inside != SIMPLE_Q)
		|| (c == '\'' && inside != DOUBLE_Q));
}

void	quote_interpret(char c, int *in)
{
	if (need_interpret_quote(c, *in))
		quote_interpretation(c, in);
}
