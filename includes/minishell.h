#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include "../lib/header_lib.h"

# define STDIN 0

// # define WORD 0
// # define CMD 1
// # define PIPE 2 
// # define LT 3 
// # define LT2 4 
// # define GT 5 
// # define GT2 6 
// # define OPTION 7

enum e_token { WORD, PIPE, LT, LT2, GT, GT2, CMD, OPTION};
enum e_quote { NO_Q, SIMPLE_Q, DOUBLE_Q};
enum e_err {QUOTES_UNCLOSED, BAD_MALLOC, BAD_INPUT};

typedef struct s_lex
{
	char			*content;
	int				token;
	int				is_builtin;
	struct s_lex	*next;
}	t_lexer;

typedef struct s_pars
{
	char *std_in;
	char **parsed;
} t_pars;

typedef struct s_env
{
	char *name;
	char *content;
	struct s_env *next;
} t_env;

typedef struct s_tree
{
	int type;
	t_lexer *cmd;
	int std_in;
	int std_out;
	struct s_tree *left;
	struct s_tree *right;

} t_tree;

typedef struct s_gen
{
	char *prompt;
	int	exit_stat;
	int status;
	int tracker;
	t_env *env;
	char **paths;
	t_lexer	*lex;
	t_pars parser;
	t_tree *ast;
}	t_gen;

/*			#Parsing#		*/

/*		token.c		*/
t_lexer	*lexer(char **cmd_line, t_gen *data);

/*	token_split.c	*/
char	**check_sub_words(char *cmd);

/*	token_insert_var.c	*/
int	insert_var(char *dst, char *src, int *src_i, t_gen *data);
int	real_size(char *content, t_gen *data);

/*	token_utils.c	*/
int		is_builtin(char *cmd);
void	quote_interpretation(char quote, int *inside);
void	display_token(t_lexer *lst_lex);

/*	env_utils.c	*/
char	*get_env_var(t_gen *gen, char *var);

/*	utils_1.c	*/
void    free_tab(char **tab);
int		is_empty(char *line);
int		len_int(int nb);

/*	temp to print something	*/
// char *g_token[8] = {"WORD", "CMD", "PIPE", "LT", "LT2", "GT", "GT2", "OPTION"};
// char *g_quote[3] = {"NO_QUOTE", "SIMPLE_QUOTE", "DOUBLE_QUOTE"};

/*			#Executor#		*/

// display/
/*		display.c	*/
void	display_prompt(t_gen *data);

// error/
/*		error.c		*/
void	arg_error(char  *exec);
void 	error(t_gen *data, int e);

// exec/
/*		exec.c		*/
void 	set_vars(t_gen *mini);

// parsing/
/*		env_vars_parsing.c		*/
void 	stock_env_vars(t_gen *data, char **env);
/*		create_pipes.c		*/
int create_pipes(t_tree *ast);

// utils/
/*		display_env_vars.c		*/
void 	display_env_vars(t_env *envs);
/*		print_tree.c		*/
void structure (t_tree *root, int level );


// executor/
/*		ast_builder.c		*/
t_tree *build_tree1(t_lexer *lexer);
t_tree *build_tree2(t_lexer *lexer);
/*		build_leaf_ast.c		*/
t_tree *build_leaf(t_lexer *lexer);

/*		build_pipe_node_ast.c		*/
t_tree *build_node(t_lexer *lex, t_lexer *head, int type);
void cut_lexer(t_lexer *head, t_lexer *lex);


#endif
