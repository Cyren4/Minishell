/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/10/27 18:14:08 by cramdani         ###   ########.fr       */
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
				start = head->hdoc_content;
		if (head->token == LT2 && redir_count == 1)
			end = head->hdoc_content;
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
	pid_t pid;
	int exit_status;
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
			std_in = readline("> ");
			breaker++;
			if (std_in == NULL)
				printf("\b\b  \b\b");
			if ((std_in && ft_strncmp(std_in, end, ft_strlen(end)) == 0 && start_flag == 1) || std_in == NULL)
				break;
			if (start_flag)
				write(fd[1], ft_strjoin(std_in, "\n"), ft_strlen(std_in) + 1);
			if (std_in && ft_strncmp(std_in, start, ft_strlen(start)) == 0)
				start_flag = 1;
			ft_free(std_in);
		}
		close(fd[1]);
		exit(1);
	}
	else
	{
		close(fd[1]);
		printf("pid = %d\n", pid);
		waitpid(pid, &exit_status, 0);
		// dup2(fd[0], ast->fd_in);
		ast->fd_in = fd[0];
		// read(ast->fd_in, buf, 1000);
		// printf("aast->fd_in:\n%s", buf);
		// close(ast->fd_in);
		// close(fd[0]);
	}
	return (pid);
}

// int store_data(char *start, char *end, t_tree *ast)
// {
// 	int start_flag;
// 	int breaker;
// 	char *std_in;
// 	int fd_tmp;

// 	fd_tmp = open("/tmp/tmp_heredoc", O_CREAT | O_RDWR, 0666);
// 	if (fd_tmp == -1)
// 		return (-1);
// 	start_flag = 0;
// 	if (!start)
// 		start_flag = 1;
// 	breaker = 0;
// 	while(1 && breaker < 10)
// 	{
// 		std_in = readline("heredoc>");
// 		breaker++;
// 		if (std_in && ft_strncmp(std_in, start, ft_strlen(start)) == 0)
// 			start_flag = 1;
// 		if (std_in && ft_strncmp(std_in, end, ft_strlen(end)) == 0)
// 			break;
// 		if (start_flag)
// 			write(fd_tmp, ft_strjoin(std_in, "\n"), ft_strlen(std_in) + 1);
// 		ft_free(std_in);
// 	}
// 	ast->fd_in = fd_tmp;
// 	return(0);
// }

int manage_redirs(t_tree *ast)
{
	t_lexer *head;
	// int file_fd;
	int flag_lt2;

	flag_lt2 = 0;
	head = ast->redir;
	while (head->next)
	{
		if (head->token == GT)
			ast->fd_out = open(head->next->content, O_CREAT | O_RDWR, 0666);
		if (head->token == GT2)
			ast->fd_out = open(head->next->content, O_CREAT | O_RDWR | O_APPEND, 0666);
		if (head->token == LT)
			ast->fd_in = open(head->next->content, O_RDONLY, 0444);
		if (head->token == LT2 && !flag_lt2)
		{
			manage_lt2(head, ast);
			flag_lt2 = 1;
		}
		head = head->next;
	}
	return (1);
}

