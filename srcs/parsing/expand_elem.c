/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:00:10 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 22:03:49 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*expand_elem(t_lexer *elm, t_gen *data)
// {
// 	char	*r_cont;
// 	int		el_i;
// 	int		i;
// 	int		in;

// 	i = 0;
// 	el_i = 0;
// 	in = NO_Q;
// 	r_cont = malloc(sizeof(char) * (real_size(elm->content, data) + 1));
// 	if (!r_cont)
// 		return (NULL);
// 	while (elm->content[el_i])
// 	{
// 		quote_interpret(elm->content[el_i], &in);
// 		if (elm->content[el_i] == '$' && in != SIMPLE_Q
// 			&& valid_e(elm->content, el_i))
// 		{
// 			i += insert_var(r_cont + i, elm->content, &el_i, data);
// 			continue ;
// 		}
// 		else
// 		{
// 			r_cont[i] = elm->content[el_i];
// 			i++;
// 		}
// 		el_i++;
// 	}
// 	r_cont[i] = '\0';
// 	ft_free(elm->content);
// 	return (r_cont);
// }
void	expand_norm(char *r_cont, char c, int *i)
{
	r_cont[*i] = c;
	*i += 1;
}

int	fuck_condition(char *str, int el_i, int in)
{
	if (str[el_i] == '$' && in == DOUBLE_Q
		&& str[el_i + 1] == '\'')
		return (0);
	return (str[el_i] == '$' && in != SIMPLE_Q
		&& valid_e(str, el_i));
}

// if (elm->content[el_i] == '$' && in != SIMPLE_Q
			// && valid_e(elm->content, el_i))
char	*expand_elem_norm(t_lexer *elm, t_gen *data, int i, int el_i)
{
	char	*r_cont;
	int		in;

	in = NO_Q;
	r_cont = malloc(sizeof(char) * (real_size(elm->content, data) + 1));
	if (!r_cont)
		return (NULL);
	while (elm->content[el_i])
	{
		quote_interpret(elm->content[el_i], &in);
		if (fuck_condition(elm->content, el_i, in))
		{
			i += insert_var(r_cont + i, elm->content, &el_i, data);
			continue ;
		}
		else
			expand_norm(r_cont, elm->content[el_i], &i);
		el_i++;
	}
	r_cont[i] = '\0';
	ft_free(elm->content);
	return (r_cont);
}

char	*expand_elem(t_lexer *elm, t_gen *data)
{
	int		el_i;
	int		i;

	i = 0;
	el_i = 0;
	return (expand_elem_norm(elm, data, i, el_i));
}
