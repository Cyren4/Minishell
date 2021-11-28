/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:36:00 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/28 16:54:21 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_lt2(t_lexer *redirs, t_tree *ast, t_gen *data)
{
	t_lexer	*head;
	char	*tmp;

	count_redirs(data, redirs);
	head = redirs;
	while (head->next)
	{
		if (head->token == LT2 && data->redirs.redir_count == 2)
			data->redirs.start = head->next->content;
		if (head->token == LT2 && data->redirs.redir_count == 1)
			data->redirs.end = head->next->content;
		if (head->token == LT2)
			data->redirs.redir_count--;
		head = head->next;
	}
	tmp = strdup_sin_quote(data->redirs.end);
	data->redirs.quote = check_quotes(data->redirs.end);
	store_data(data->redirs.start,
		tmp, ast, data);
	free(tmp);
	return (data->redirs.fd_in);
}

int	r_size_herdoc(char *content, t_gen *data)
{
	int		total_size;
	int		i;

	i = 0;
	total_size = 0;
	while (content[i])
	{
		if (content[i] == '$' && valid_e(content, i))
		{
			total_size += var_size(content, &i, data);
			continue ;
		}
		else
			total_size++;
		i++;
	}
	return (total_size);
}

char	*expand_heredoc(char *std_in)
{
	char	*expanded;
	t_gen	*data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = get_data(NULL);
	expanded = malloc(sizeof(char) * (r_size_herdoc(std_in, data) + 1));
	if (!expanded)
		return (std_in);
	while (std_in[i])
	{
		if (std_in[i] == '$' && valid_e(std_in, i))
		{
			j += insert_var(expanded + j, std_in, &i, data);
			continue ;
		}
		else
			expand_norm(expanded, std_in[i], &j);
		i++;
	}
	expanded[j] = '\0';
	free(std_in);
	return (expanded);
}

void	sub_send_data(t_gen *data, char *start, char *end, int i)
{
	if (i == 1)
	{
		data->redirs.start_flag = 0;
		if (!start)
			data->redirs.start_flag = 1;
	}
	if (i == 2)
	{
		clean_redir(data);
		if (end)
			ft_free(end);
		if (start)
			ft_free(start);
		exit(1);
	}
}

void	send_data_bis(t_gen *data, int *fd, char *start)
{
	if (!data->redirs.quote)
		data->redirs.std_in = expand_heredoc(data->redirs.std_in);
	data->redirs.tmp = ft_strjoin(data->redirs.std_in, "\n");
	if (data->redirs.start_flag)
		write(fd[1], data->redirs.tmp, ft_strlen(data->redirs.std_in) + 1);
	if (data->redirs.std_in
		&& ft_strncmp(data->redirs.std_in, start, ft_strlen(start)) == 0)
		data->redirs.start_flag = 1;
	ft_free(data->redirs.std_in);
	free(data->redirs.tmp);
}
