/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/05 14:37:46 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void manage_lt2(t_lexer *redirs)
{
	t_lexer *head;
	int redir_count;

	head = redirs;
	redir_count = 0;
	while (head->next != NULL)
	{
		if (head->token == LT2)
			redir_count++;
		head = head->next;
	}
	while (head->next && redir_count > 2)
	{
		if (head->next->token == LT2)
		{
			head->next = head->next->next;
			redir_count--;
		}
		head = head->next;
	}
}

int manage_redirs(t_tree *ast)
{
	t_lexer *head;
	int file_fd;

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
		if (head->token == LT2)
			manage_lt2(head);
		head = head->next;
	}
	return (1);
}