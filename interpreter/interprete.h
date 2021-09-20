/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:59:53 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/20 18:49:28 by vbaron           ###   ########.fr       */
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



typedef struct s_tree
{
	int type;
	t_lexer *curr_lex;
	struct s_tree *left;
	struct s_tree *right;

} t_tree;

int build_pipe(t_tree *ast, t_lexer *lex, t_lexer *head);
int build_tree(t_tree *ast, t_lexer *lexer);
t_lexer *add_custom_elem_to_lexer(t_lexer *lexer, char *content, int token);
