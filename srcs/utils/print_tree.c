/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:08:22 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/23 17:10:59 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void padding(char ch, int n)
{
	int i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void structure(t_tree *root, int level)
{
	char *types[5] = {"PIPE", "<", "<<", ">", ">>"};
	
	t_lexer *lex;
	if (root == NULL)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		structure(root->right, level + 1);
		padding('\t', level);
		if (root->cmd)
		{
			lex = root->cmd;
			while (lex)
			{
				printf("%s ", lex->content);
				lex = lex->next;
			}
		}
		else
			printf("%s", types[root->type]);	
		printf("\n");
		structure(root->left, level + 1);
	}
}