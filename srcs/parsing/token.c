/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:26:49 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/05 17:54:27 by cramdani         ###   ########.fr       */
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
			// if (in == DOUBLE_Q || ft_strncmp(elm->content + el_i, "$?", 2) == 0)
				i += insert_var(r_cont + i, elm->content, &el_i, data);
			// else
				// i += ins_v_nq(r_cont + i, elm->content, &el_i, data);
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

int	nb_word(char *cmd)
{
	int	inside;
	int	i;
	int	count;

	i = 0;
	count = 0;
	inside = NO_Q;
	while (cmd && cmd[i])
	{
		while (cmd && cmd[i])
		{
			if ((cmd[i] == '"' && inside != SIMPLE_Q)
			|| (cmd[i] == '\'' && inside != DOUBLE_Q))
				quote_interpretation(cmd[i], &inside);
			if (cmd[i] == ' ' && inside == NO_Q)
				break ;
			i++;
		}
		count++;
		while (cmd && cmd[i] && cmd[i] == ' ')
			i++;
	}
	return (count);
}
// sub_word = start, len, num mot
char	**split_w(char *cmd)
{
	char	**ret;
	int		inside;
	int		sub_word[3];
	int		i;

	i = 0;
	sub_word[2] = 0;
	inside = NO_Q;
	ret = malloc(sizeof(char *) * (nb_word(cmd) + 1));
	if (!ret)
		return (NULL);
	while (cmd && cmd[i])
	{
		sub_word[0] = i;
		sub_word[1] = 0;
		while (cmd && cmd[i + sub_word[1]])
		{
			printf("\nbefore |%c|: %d\n", cmd[i + sub_word[1]], inside);
			if ((cmd[i] == '"' && inside != SIMPLE_Q)
			|| (cmd[i] == '\'' && inside != DOUBLE_Q))
				quote_interpretation(cmd[i + sub_word[1]], &inside);
			printf("\nafter |%c|: %d\n", cmd[i + sub_word[1]], inside);
			if (cmd[i + sub_word[1]] == ' ' && inside == NO_Q)
				break ;
			sub_word[1]++;
		}
		ret[sub_word[2]] = ft_substr(cmd, sub_word[0], sub_word[1]);
		sub_word[2]++;
		i += sub_word[1];
		while (cmd && cmd[i] == ' ')
			i++;
	}
	ret[sub_word[2]] = NULL; 
	free(cmd);
	return (ret);
}

//dup sans caracter 
char	*strdup_sin_quote(char *s1)
{
	int		inside;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	inside = NO_Q;
	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		if ((s1[i] == '"' && inside != SIMPLE_Q)
			|| (s1[i] == '\'' && inside != DOUBLE_Q))
			quote_interpretation(s1[i], &inside);
		else
		{
			str[j] = s1[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

t_lexer	*get_words(t_lexer *head)
{
	char	**tmp;
	t_lexer	*new;
	t_lexer	*tmp_new;
	int		i;

	i = 1;
	tmp = split_w(ft_strtrim(head->content, " "));
	for (int index = 0; tmp[index] != NULL; index++)
		printf("word %d: |%s|\n", index, tmp[index]);
	if (tmp == NULL)
		return (NULL);
	tmp_new = head;
	free(head->content);
	head->content = strdup_sin_quote(tmp[0]);
	// head->content = ft_strdup(tmp[0]);
	while (tmp[i] != NULL)
	{
		new = malloc(sizeof(t_lexer));
		new->token = WORD;
		new->content = ft_strdup(tmp[i]);
		new->content = strdup_sin_quote(tmp[i]);
		// new->content = ft_strdup(tmp[i]);
		new->next = NULL;
		tmp_new->next = new;
		tmp_new = tmp_new->next;
		i++;
	}
	free_tab(tmp);
	return (head);
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
	if (lst_elem == NULL)
		return (get_words(new));
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (data->hdoc == 1 && new->token != LT2)
	{
		data->hdoc = 0;
		tmp->hdoc_content = ft_strdup(cmd);
	}
	tmp->next = get_words(new);
	return (lst_elem);
}

int	is_redir(int token)
{
	return (token == LT || token == GT || token == LT2 || token == GT2);
}

char	*get_token(int token)
{
	if (token == PIPE)
		return ("|");
	else if (token == LT)
		return ("<");
	else if (token == LT2)
		return ("<<");
	else if (token == GT)
		return (">");
	else if (token == GT)
		return (">>");
	return ("");
}

int	check_syntax(t_lexer *lex)
{
	t_lexer	*tmp;
	int		ret;

	tmp = lex;
	ret = -1;
	if (lex != NULL && lex->token == PIPE)
		ret = PIPE;
	while (tmp && ret == -1)
	{
		if (tmp->token == PIPE && (tmp->next == NULL
			|| tmp->next->token == PIPE))
			ret = PIPE;
		else if (is_redir(tmp->token) && tmp->next != NULL
				&& is_redir(tmp->next->token))
			ret = tmp->token;
		tmp = tmp->next;
	}
	if (ret != -1)
		print_error("bash: syntax error near unexpected token `",
			get_token(ret), "\'\n");
	return (ret);
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
