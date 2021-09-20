/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:59:53 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/20 16:26:53 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "../lib/libft/libft.h"
#include "../includes/minishell.h"

typedef struct s_lexer
{
	char *content;
	int token;
	struct s_lexer *next;
	struct s_lexer *prev;

} t_lexer;

typedef struct s_tree
{
	t_lexer *head;
	t_lexer *curr_pos;
	struct s_tree *left;
	struct s_tree *right;

} t_tree;

typedef struct s_gen
{
	t_lexer *lex;
} t_gen;