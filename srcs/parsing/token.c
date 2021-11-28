/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:26:49 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/28 17:27:34 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_lexer	*norm_lexer(t_gen *data)
{
	if (check_syntax(data->lex) != -1)
	{
		data->status = -1;
		get_exit_stat(2);
	}
	free_tab(data->parser.parsed);
	return (data->lex);
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
	return (norm_lexer(data));
}
