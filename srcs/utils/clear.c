/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/23 23:22:22 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_lex(t_lexer *lex)
{
	t_lexer	*cur;
	t_lexer	*old;

	if (lex == NULL)
		return ;
	cur = lex;
	while (cur)
	{
		if (cur->content)
			free(cur->content);
		old = cur;
		cur = cur->next;
		if (old)
			free(old);
	}
	lex = NULL;
}

void	clean_envx(t_gen *data)
{
	t_env	*cur;
	t_env	*next;

	if (data->env == NULL)
		return ;
	cur = data->env;
	while (cur != NULL)
	{
		ft_free(cur->name);
		ft_free(cur->content);
		next = cur->next;
		ft_free(cur);
		cur = next;
	}
}

void	clean_env(t_gen *data)
{
	int		i;

	clean_envx(data);
	if (data->paths)
	{
		i = -1;
		while (data->paths[++i])
			if (data->paths[i])
				ft_free(data->paths[i]);
		ft_free(data->paths);
	}
}

void	clean_parser(t_pars *pars)
{
	int	i;

	i = 0;
	if (pars == NULL)
		return ;
	if (pars->parsed)
	{
		while (pars->parsed[i])
		{
			if (pars->parsed[i])
				ft_free(pars->parsed[i]);
			i++;
		}
	}
	ft_free(pars->parsed);
	if (pars->std_in)
		ft_free(pars->std_in);
}

void	clean_tree(t_tree *ast)
{
	t_tree	*head;

	head = ast;
	if (head && head->type == CMD)
	{
		if (head->cmd)
			clean_lex(head->cmd);
		if (head->redir)
			clean_lex(head->redir);
	}
	if (head && head->left)
		clean_tree(head->left);
	if (head && head->right)
		clean_tree(head->right);
	if (head)
		ft_free(head);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

void	clean_child(t_gen *data)
{
	close_pipes(data->ast);
	clean_data(data);
	free_tab(data->cmd_table);
	free(data->cmd);
	clean_envx(data);
	free(data->home);
	ft_free(data->prompt);
}

void	clean_data(t_gen *data)
{
	clean_tree(data->ast);
	if (data->paths != NULL)
		free_tab(data->paths);
	data->ast = NULL;
	data->lex = NULL;
	free(data->parser.std_in);
	free_tab(data->parser.parsed);
	data->parser.parsed = NULL;
	data->ast = NULL;
	data->str_err = NULL;
	data->status = 1;
	free(data->pids);
}

void	delete_data(t_gen *data)
{
	ft_free(data->home);
	ft_free(data->prompt);
	data->lex = NULL;
	clean_env(data);
	if (data->ast != NULL)
		clean_tree(data->ast);
	clear_history();
}

void	clean_exit(t_gen *data)
{
	clean_data(data);
	ft_free(data->home);
	ft_free(data->prompt);
	clean_envx(data);
	clear_history();
}
