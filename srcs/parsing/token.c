/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:26:49 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/27 16:47:17 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	complexe_elem(t_lexer *elem, t_gen *data)
{
	char	*real_content;
	int		elem_i;
	int		i;
	int		inside;

	i = 0;
	elem_i = 0;
	inside = NO_Q;
	real_content = malloc(sizeof(char) * (real_size(elem->content, data) + 1));
	while (elem->content[elem_i])
	{
		if (elem->content[elem_i] == '"' || elem->content[elem_i] == '\'')
			quote_interpretation(elem->content[elem_i], &inside);
		else if (elem->content[elem_i] == '$' && inside != SIMPLE_Q)
		{
			if (inside == DOUBLE_Q || ft_strncmp(elem->content + elem_i, "$?", 2) == 0)
				i += insert_var(real_content + i, elem->content, &elem_i, data);
			else
				i += insert_var_noquote(real_content + i, elem->content, &elem_i, data);
			continue ;
		}
		else
		{
			real_content[i] = elem->content[elem_i];
			i++;
		}
		elem_i++;
	}
	real_content[i] = '\0';
	ft_free(elem->content);
	elem->content = real_content;
}

int	check_type(t_lexer *elem, t_gen *data)
{
	if (ft_strcmp(elem->content, "|") == 0)
		elem->token = PIPE;
	else if (ft_strcmp(elem->content, "<") == 0)
		elem->token = LT;
	else if (ft_strcmp(elem->content, "<<") == 0)
	{
		data->hdoc = 1;
		elem->token = LT2;
	}
	else if (ft_strcmp(elem->content, ">") == 0)
		elem->token = GT;
	else if (ft_strcmp(elem->content, ">>") == 0)
		elem->token = GT2;
	else
	{
		complexe_elem(elem, data);
		elem->token = WORD;
		if (is_builtin(elem->content))
		{
			elem->token = CMD;
			elem->is_builtin = 1;
		}
	}
	return (1);
}

t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd, t_gen *data)
{
	t_lexer	*new;
	t_lexer	*tmp;
	
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = ft_strdup(cmd);
	new->is_builtin = 0;
	new->next = NULL;
	check_type(new, data);
	if (lst_elem == NULL)
		return (new);
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->hdoc_content = NULL;
	if (data->hdoc == 1 && new->token != LT2)
	{
		tmp->hdoc_content = ft_strdup(cmd);
		data->hdoc = 0;
	}
	tmp->next = new;
	return (lst_elem);
}

t_lexer	*lexer(char **cmd_line, t_gen *data)
{
	// t_lexer	*lst_elem;
	int		i;
	int		j;
	char	**splited;

	// lst_elem = NULL;
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
	return (data->lex);
}
