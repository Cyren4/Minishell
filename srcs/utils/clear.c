/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/18 12:44:59 by vbaron           ###   ########.fr       */
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
			free(old);
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
			free(cur->name);
		if (cur->content != NULL)
			free(cur->content);
		next = cur->next;
		if (cur)
			free(cur);
		cur = next;
	}
	if (data->paths)
	{
		i = -1;
		while (data->paths[++i])
		{
			if (data->paths[i])
				free(data->paths[i]);
		}
		free(data->paths);
	}
	
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
				free(pars->parsed[i]);
			i++;
		}
	}
	free(pars->parsed);
	if (pars->std_in)
		free(pars->std_in);
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
		free(head);
		head = NULL;
	}
}