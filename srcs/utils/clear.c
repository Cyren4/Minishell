/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/16 15:33:17 by cramdani         ###   ########.fr       */
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

void	clean_env(t_gen *data)
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

void	clean_data(t_gen *data)
{
	clean_tree(data->ast);
	if (data->paths != NULL)
		free_tab(data->paths);
	data->ast = NULL;
	data->lex = NULL;
	data->hdoc = 0;
	free(data->parser.std_in );
	free_tab(data->parser.parsed);
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->ast = NULL;
	data->str_err = NULL;
	data->status = 1;
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

	// if (data->paths)
		// free_tab(data->paths);