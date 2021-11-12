/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:26:49 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/12 15:48:49 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check si expansion valide 
//(soit $? ou au moins lettre/_)
int	valid_e(char *content, int index)
{
	return (ft_isalpha(content[index + 1])
			|| content[index + 1] == '_'
			|| content[index + 1] == '?');
}

	// if (in == DOUBLE_Q || ft_strncmp(elm->content + el_i, "$?", 2) == 0)
	// else
	// i += ins_v_nq(r_cont + i, elm->content, &el_i, data);
void	complexe_elem(t_lexer *elm, t_gen *data)
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

int	check_type(t_lexer *elem, t_gen *data)
{
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
	if (new->token == LT2)
		data->hdoc = 1;
	if (lst_elem == NULL && new->token == WORD)
		return (new);
		// return (get_words(new));
	else if (lst_elem == NULL)
		return (new);
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (data->hdoc == 1 && new->token != LT2)
	{
		data->hdoc = 0;
		tmp->hdoc_content = ft_strdup(cmd);
	}
	tmp->next = get_words(new);
	// tmp->next = new;
	return (lst_elem);
}

t_lexer	*lexer(char **cmd_line, t_gen *data)
{
	int		i;
	int		j;
	char	**splited;

	data->hdoc = 0;
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
		data->exit_stat = 2;
	}
	return (data->lex);
}
