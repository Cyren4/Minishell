/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/11 20:54:04 by vincentbaro      ###   ########.fr       */
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

void    clean_env(t_env *env)
{
	t_env *cur;
	t_env *next;

	if (env == NULL)
		return;
	cur = env;
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