/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:26:49 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/24 17:10:40 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	complexe_elem1(t_lexer *elm, t_gen *data)
{
	char	*r_cont;
	int		el_i;
	int		i;
	int		in;

	i = 0;
	el_i = 0;
	in = NO_Q;
	r_cont = malloc(sizeof(char) * (real_size(elm->content, data) + 1));
	if (!r_cont)
		return ;
	while (elm->content[el_i])
	{
		if ((elm->content[el_i] == '"' && in != SIMPLE_Q)
			|| (elm->content[el_i] == '\'' && in != DOUBLE_Q))
			quote_interpretation(elm->content[el_i], &in);
		if (elm->content[el_i] == '$' && in != SIMPLE_Q
			&& valid_e(elm->content, el_i))
		{
			i += insert_var(r_cont + i, elm->content, &el_i, data);
			continue ;
		}
		else
		{
			r_cont[i] = elm->content[el_i];
			i++;
		}
		el_i++;
	}
	r_cont[i] = '\0';
	ft_free(elm->content);
	elm->content = r_cont;
}
*/

char	*expand_elem(t_lexer *elm, t_gen *data)
{
	char	*r_cont;
	int		el_i;
	int		i;
	int		in;

	i = 0;
	el_i = 0;
	in = NO_Q;
	r_cont = malloc(sizeof(char) * (real_size(elm->content, data) + 1));
	if (!r_cont)
		return (NULL);
	while (elm->content[el_i])
	{
		if (need_interpret_quote(elm->content[el_i], in))
			quote_interpretation(elm->content[el_i], &in);
		if (elm->content[el_i] == '$' && in != SIMPLE_Q
			&& valid_e(elm->content, el_i))
		{
			i += insert_var(r_cont + i, elm->content, &el_i, data);
			continue ;
		}
		else
		{
			r_cont[i] = elm->content[el_i];
			i++;
		}
		el_i++;
	}
	r_cont[i] = '\0';
	ft_free(elm->content);
	return (r_cont);
}

void	check_type_norm(t_lexer *elem, t_gen *data)
{
	if (!is_tild_exp(elem, data) && !is_redir(data->prev_token))
		elem->content = expand_elem(elem, data);
	elem->token = WORD;
	if (is_builtin(elem->content))
	{
		elem->token = CMD;
		elem->is_builtin = 1;
	}
}

int	check_type(t_lexer *elem, t_gen *data)
{
	int	ret;

	if (ft_strcmp(elem->content, "|") == 0)
		elem->token = PIPE;
	else if (ft_strcmp(elem->content, "<") == 0)
		elem->token = LT;
	else if (ft_strcmp(elem->content, "<<") == 0)
		elem->token = LT2;
	else if (ft_strcmp(elem->content, ">") == 0)
		elem->token = GT;
	else if (ft_strcmp(elem->content, ">>") == 0)
		elem->token = GT2;
	else
		check_type_norm(elem, data);
	ret = data->prev_token;
	data->prev_token = elem->token;
	return (ret);
}

t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd, t_gen *data)
{
	t_lexer	*new;
	t_lexer	*tmp;
	int		old_token;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	old_token = -1;
	new->content = ft_strdup(cmd);
	new->is_builtin = 0;
	new->next = NULL;
	old_token = check_type(new, data);
	if (lst_elem == NULL)
		return (get_words(new, old_token));
	else if (lst_elem == NULL)
		return (new);
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = get_words(new, old_token);
	return (lst_elem);
}

t_lexer	*lexer(char **cmd_line, t_gen *data)
{
	int		i;
	int		j;
	char	**splited;

	data->prev_token = -1;
	data->lex = NULL;
	i = 0;
	while (cmd_line[i] != NULL)
	{
		j = 0;
		splited = NULL;
		splited = check_sub_words(cmd_line[i]);
		while (splited[j] != NULL)
		{
			data->lex = add_elem_lex(data->lex, splited[j], data);
			j++;
		}
		if (splited)
			free_tab(splited);
		i++;
	}
	if (check_syntax(data->lex) != -1)
	{
		data->status = -1;
		get_exit_stat(2);
	}
	return (data->lex);
}
