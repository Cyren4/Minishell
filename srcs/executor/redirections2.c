/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:34:27 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/28 17:03:21 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	send_data(t_gen *data, int *fd, char *start, char *end)
{
	data->redirs.std_in = NULL;
	sub_send_data(data, start, end, 1);
	while (1)
	{
		data->redirs.std_in = readline("> ");
		if (data->redirs.std_in == NULL)
		{
			print_error("minishell: warning: here-document \
at line 1 delimited by end-of-file (wanted `", end, "')\n");
			break ;
		}
		if ((data->redirs.std_in
				&& ft_strncmp(data->redirs.std_in, end, ft_strlen(end)) == 0
				&& data->redirs.start_flag == 1) || data->redirs.std_in == NULL)
			break ;
		send_data_bis(data, fd, start);
	}
	close(fd[1]);
}

void	store_data(char *start, char *end, t_tree *ast, t_gen *data)
{
	int		fd[2];

	data->redirs.std_in = NULL;
	if (pipe(fd) < 0)
		return ;
	send_data(data, fd, start, end);
	ast->fd_in = fd[0];
}

int	manage_lt1(t_lexer *head, t_tree *ast)
{
	if (head->token == LT)
	{
		ast->fd_in = open(head->next->content, O_RDONLY, 0444);
		if (ast->fd_in == -1)
		{
			print_error("minishell: ",
				head->next->content, ": ");
			perror("");
			return (0);
		}
	}
	return (1);
}

void	manage_gt(t_lexer *head, t_tree *ast, t_gen *data)
{
	if (is_redir(head->token) && head->token != LT2)
		head->next->content = expand_redir(data, head->next);
	if (head->token == GT)
		ast->fd_out = open(head->next->content, O_CREAT | O_RDWR, 0666);
	if (head->token == GT2)
		ast->fd_out = open(head->next->content,
				O_CREAT | O_RDWR | O_APPEND, 0666);
}

int	manage_redirs(t_tree *ast, t_gen *data)
{
	t_lexer	*head;
	int		flag_lt2;

	flag_lt2 = 0;
	head = ast->redir;
	while (head->next)
	{
		manage_gt(head, ast, data);
		if (!manage_lt1(head, ast))
			return (0);
		if ((head->token == GT || head->token == GT2) && ast->fd_out == -1)
		{
			print_error("minishell: ", head->next->content, ": ");
			perror("");
			return (0);
		}
		if (head->token == LT2 && !flag_lt2)
		{
			signal(SIGINT, sig_int);
			manage_lt2(head, ast, data);
			flag_lt2 = 1;
		}
		head = head->next;
	}
	return (1);
}
