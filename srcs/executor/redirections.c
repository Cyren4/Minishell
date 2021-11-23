/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:49:43 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/23 18:43:22 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_quotes(char *end)
{
	int i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\"' || end[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*end_sin_quote(char *end)
{
	char	*tmp;

	tmp = strdup_sin_quote(end);
	free(end);
	return (tmp);
}

int	manage_lt2(t_lexer *redirs, t_tree *ast, t_gen *data)
{
	t_lexer	*head;
	int		redir_count;
	int		fd_in;
	char	*start;
	char	*end;

	// printf("la->%s\n", head->next->content);
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
	fd_in = store_data(start, strdup_sin_quote(end), ast, check_quotes(end), data);
	return (fd_in);
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

/* tests
bash-5.0$ cat << ok
> $a
> ok
ok

bash-5.0$ cat << ok
> ok""
> ok''
> 'ok'
> ok
ok""
ok''
'ok'

bash-5.0$ cat << ok
> '$USER'
> 
> ok
'cramdani'

bash-5.0$ export a="ok        o"
bash-5.0$ cat << ok
> $a
> ok
ok        o
*/
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
		{
			expanded[j] = std_in[i];
			j++;
		}
		i++;
	}
	expanded[j] = '\0';
	free(std_in);
	return (expanded);
}

int	store_data(char *start, char *end, t_tree *ast, int quote, t_gen *data)
{
	int		fd[2];
	char	*std_in;
	int		start_flag;
	pid_t	pid;
	int		exit_status;
	// int		quote;
	
	// quote = check_quotes(end);
	// breaker = 0;
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
		while (1)
		{
			std_in = readline("> ");
			if (std_in == NULL)
			{
				print_error("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", end, "')\n");
				break;
			}
			// breaker++;
			if ((std_in && ft_strncmp(std_in, end, ft_strlen(end)) == 0
					&& start_flag == 1) || std_in == NULL)
				break ;
			if (!quote)
				std_in = expand_heredoc(std_in);
			if (start_flag)
				write(fd[1], ft_strjoin(std_in, "\n"), ft_strlen(std_in) + 1);
			if (std_in && ft_strncmp(std_in, start, ft_strlen(start)) == 0)
				start_flag = 1;
			ft_free(std_in);
		}
		close(fd[1]);
		clean_child(data);
		exit(1);
	}
	else
	{
		close(fd[1]);
		// printf("pid = %d\n", pid);
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

char	*expand_redir(t_gen *data, t_lexer *fd)
{
	char	*tmp;

	fd->content = expand_elem(fd, data);
	tmp = strdup_sin_quote(fd->content);
	free(fd->content);
	return (tmp);
}

int	manage_redirs(t_tree *ast, t_gen *data)
{
	t_lexer	*head;
	int		flag_lt2;

	flag_lt2 = 0;
	head = ast->redir;
	while (head->next)
	{
		if (is_redir(head->token) && head->token != LT2)
			head->next->content = expand_redir(data, head->next); 
		if (head->token == GT)
			ast->fd_out = open(head->next->content, O_CREAT | O_RDWR, 0666);
		if (head->token == GT2)
			ast->fd_out
				= open(head->next->content, O_CREAT | O_RDWR | O_APPEND, 0666);
		if (head->token == LT)
		{
			ast->fd_in = open(head->next->content, O_RDONLY, 0444);
			if (ast->fd_in == -1)
			{
				print_error("minishell: ", head->next->content,": No such file or directory\n");
				return (0);
			}
		}
		if (head->token == LT2 && !flag_lt2)
		{
			manage_lt2(head, ast, data);
			flag_lt2 = 1;
		}
		head = head->next;
	}
	return (1);
}
