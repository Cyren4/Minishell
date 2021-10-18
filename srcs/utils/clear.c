/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/18 15:28:24 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    clean_lex(t_lexer *lex)
{
	t_lexer *cur;
	t_lexer *old;

	if (lex == NULL)
		return;
	cur = lex;
	while (cur)
	{
		old = cur;
		cur = cur->next;
		if (old)
			ft_free(old);
	}
}

void    clean_env(t_gen *data)
{
	t_env *cur;
	t_env *next;
	int i;

	if (data->env == NULL)
		return;
	cur = data->env;
	while (cur != NULL)
	{
		if (cur->name != NULL)
			ft_free(cur->name);
		if (cur->content != NULL)
			ft_free(cur->content);
		next = cur->next;
		if (cur)
			ft_free(cur);
		cur = next;
	}
	if (data->paths)
	{
		i = -1;
		while (data->paths[++i])
		{
			if (data->paths[i])
				ft_free(data->paths[i]);
		}
		ft_free(data->paths);
	}
	if (data->pwd)
		ft_free(data->pwd);
	
}

void    clean_parser(t_pars *pars)
{
	int i;

	i = 0;
	if (pars == NULL)
		return;
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

void clean_tree(t_tree *ast)
{
	t_tree *head;

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
	{
		ft_free(head);
		head = NULL;
	}
}

void ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}