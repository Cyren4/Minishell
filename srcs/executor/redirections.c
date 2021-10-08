/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/08 14:27:53 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int manage_lt2(t_lexer *redirs, t_tree *ast)
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
		if (head->token == LT2 && redir_count == 2)
			start = head->next->content;
		if (head->token == LT2 && redir_count == 1)
			end = head->next->content;
		if (head->token == LT2)
			redir_count--;
		head = head->next;
	}
	fd_in = store_data(start, end, ast);
	return (fd_in);
}

int store_data(char *start, char *end, t_tree *ast)
{
	int fd[2];
	char *std_in;
	int start_flag;
	int pid;
	int breaker;
	// char buf[1000];
	(void)ast;
	breaker = 0;

	std_in = NULL;
	if (pipe(fd) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		start_flag = 0;
		if (!start)
			start_flag = 1;
		while(1 && breaker < 10)
		{
			std_in = readline(">");
			breaker++;
			if (std_in && ft_strncmp(std_in, start, ft_strlen(start)) == 0)
				start_flag = 1;
			if (std_in && ft_strncmp(std_in, end, ft_strlen(end)) == 0)
				break;
			if (start_flag)
				write(fd[1], ft_strjoin(std_in, "\n"), ft_strlen(std_in) + 1);
		}
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		// read(fd[0], buf, 1000);
		// printf("buf : %s\n", buf);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (1);
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
			file_fd = open(head->next->content, O_CREAT | O_RDWR, 0666);
			if (ast->fd_out != 1)
				close(ast->fd_out);
			dup2(file_fd, STDOUT_FILENO);
			close(file_fd);
		}
		if (head->token == GT2)
		{
			file_fd = open(head->next->content, O_CREAT | O_RDWR | O_APPEND, 0666);
			if (ast->fd_out != 1)
				close(ast->fd_out);
			dup2(file_fd, STDOUT_FILENO);
			close(file_fd);
		}
		if (head->token == LT)
		{
			file_fd = open(head->next->content, O_RDONLY, 0444);
			if (ast->fd_in != 0)
				close(ast->fd_in);
			dup2(file_fd, STDIN_FILENO);
			close(file_fd);
		}
		if (head->token == LT2 && !flag_lt2)
		{
			if (ast->fd_in != 0)
				close(ast->fd_in);
			manage_lt2(head, ast);
			flag_lt2 = 1;
		}
		head = head->next;
	}
	return (1);
}