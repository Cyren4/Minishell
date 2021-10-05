/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/05 17:43:01 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int manage_lt2(t_lexer *redirs)
{
	t_lexer *head;
	int redir_count;
	int fd_in;
	char *start;
	char *end;

	start = NULL;
	end = NULL;
	head = redirs;
	redir_count = 0;
	while (head->next != NULL)
	{
		if (head->token == LT2)
			redir_count++;
		head = head->next;
	}
	head = redirs;
	while (head->next)
	{
		if ( head->token == LT2 && redir_count == 2)
			start = head->next->content;
		if (head->token == LT2 && redir_count == 1)
			end = head->next->content;
		if (head->token == LT2)
			redir_count--;
		head = head->next;
	}
	fd_in = store_data(start, end);
	return (fd_in);
}

int store_data(char *start, char *end)
{
	int fd;
	
	fd = open("tmp", O_CREAT | O_APPEND)
}

int manage_redirs(t_tree *ast)
{
	t_lexer *head;
	int file_fd;
	int flag_lt2;

	flag_lt2 = 0;
	head = ast->redir;
	while (head->next)
	{
		if (head->token == GT)
		{
			file_fd = open(head->next->content, O_CREAT | O_RDWR | O_APPEND, 0666);
			dup2(file_fd, ast->fd_out);
		}
		if (head->token == GT2)
		{
			file_fd = open(head->next->content, O_CREAT | O_RDWR | O_APPEND, 0666);
			dup2(file_fd, ast->fd_out);
		}
		if (head->token == LT)
		{
			file_fd = open(head->next->content, O_RDONLY, 0444);
			dup2(file_fd, ast->fd_in);
		}
		if (head->token == LT2 && !flag_lt2)
		{
			manage_lt2(head);
			flag_lt2 = 1;
		}
		head = head->next;
	}
	return (1);
}