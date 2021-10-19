/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:51:50 by cramdani          #+#    #+#             */
/*   Updated: 2021/10/16 08:21:20 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    clean_lex(t_lexer *lex)
{
	t_lexer *cur;
	t_lexer *next;

	if (lex == NULL)
		return;
	cur = lex;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void    clean_env(t_env *env)
{
	t_env *cur;
	t_env *next;

	if (env == NULL)
		return;
	cur = env;
	while (env != NULL)
	{
		next = env->next;
		if (cur->name != NULL)
			free(cur->name);
		if (cur->content != NULL)
			free(cur->content);
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
	pars->parsed = NULL;
}
