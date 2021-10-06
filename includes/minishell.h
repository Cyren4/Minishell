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
# include <limits.h>
# include <errno.h>

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
	struct s_lex	*prev;
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
	t_lexer *redir;
	int fd_in;
	char *input;
	int fd_out;
	char *output;
	struct s_tree *left;
	struct s_tree *right;

} t_tree;

typedef struct s_gen
{
	char	*prompt;
	char	*pwd;
	int		exit_stat;
	int		status;
	int		tracker;
	t_env	*env;
	char	**paths;
	t_lexer	*lex;
	t_pars parser;
	t_tree *ast;
	int std_out;
	int std_in;
	int std_err;
	char *str_err;
}	t_gen;

/*			#Parsing#		*/

/*		token.c		*/
t_lexer	*lexer(char **cmd_line, t_gen *data);

/*		token_split.c	*/
char	**check_sub_words(char *cmd);

/*	token_insert_var.c	*/
int		insert_var(char *dst, char *src, int *src_i, t_gen *data);
int		real_size(char *content, t_gen *data);

/*	token_utils.c	*/
int		is_builtin(char *cmd);
void	quote_interpretation(char quote, int *inside);
void	display_token(t_lexer *lst_lex);

/*	env_utils.c	*/
char	*get_env_var(t_gen *gen, char *var);
char	*get_var_exist(t_gen *gen, char *var);


/*			#Executor#		*/

//	builtin/

/*		unset.c		*/
void	free_env(t_env *env);
void	ft_unset(t_gen *data, t_lexer *cmd);

/*		export.c	*/
void	ft_export(t_gen *data, t_lexer *cmd);
void	ft_unset(t_gen *data, t_lexer *cmd);

/*		env.c	*/
void	ft_env(t_gen *data, char *pref);

/*		cd.c	*/
void	ft_cd(t_gen *data, t_lexer *dir);

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
/*		is_execve.c		*/
char *is_excve(char *command, t_gen *data);

// parsing/
/*		env_vars_parsing.c		*/
void 	stock_env_vars(t_gen *data, char **env);
void display_array(char **path);
void	add_elem(t_gen *data, char *var_path);
/*		create_pipes.c		*/
int		create_pipes(t_tree *ast);



// executor/
/*		ast_builder.c		*/
t_tree *build_tree1(t_lexer *lexer);
t_tree *build_tree2(t_lexer *lexer);

/*		build_leaf_ast.c		*/
t_tree *build_leaf(t_lexer *lexer);

/*		build_pipe_node_ast.c		*/
t_tree *build_node(t_lexer *lex, t_lexer *head, int type);
void cut_lexer(t_lexer *head, t_lexer *lex);
/*		execute_ast.c		*/
int execute_ast(t_gen *data, t_tree *ast);
/*		execute_command.c		*/
int execute_command(t_gen *data, t_tree *ast);
/*		execute_command.c		*/
int execute_redir(t_gen *data, t_tree *ast);
/*		signals.c		*/
void exit_shell(int sig);
/*		redirections.c		*/
int manage_redirs(t_tree *ast);
int manage_lt2(t_lexer *redirs, t_tree *ast);
int store_data(char *start, char *end, t_tree *ast);

/*			#utils#		*/

/*	utils_1.c	*/
void	free_tab(char **tab);
int		is_empty(char *line);
int		len_int(int nb);
int		occur(char *str, char c, int nbOccur);

/*		display_env_vars.c		*/
void 	display_env_vars(t_env *envs);

/*		print_tree.c		*/
void	structure(t_tree *root, int level );


/*		print_tree.c		*/
void	clean_lex(t_lexer *lex);
void    clean_env(t_env *env);
void    clean_parser(t_pars *pars);

/*		execute_ast.c		*/
int 	execute_ast(t_gen *data, t_tree *ast);

/*		execute_command.c		*/
int 	execute_command(t_gen *data, t_tree *ast);

/*		execute_command.c		*/
int 	execute_redir(t_gen *data, t_tree *ast);

/*		signals.c		*/
void 	exit_shell(int sig);

/*		redirections.c		*/
int manage_redirs(t_tree *ast);
int manage_lt2(t_lexer *redirs, t_tree *ast);
int store_data(char *start, char *end, t_tree *ast);

#endif
