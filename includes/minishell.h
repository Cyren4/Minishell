/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:30:08 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/17 19:14:06 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

enum e_token {PIPE, LT, LT2, GT, GT2, CMD, OPTION, WORD};
enum e_quote { NO_Q, SIMPLE_Q, DOUBLE_Q};
enum e_err {QUOTES_UNCLOSED, BAD_MALLOC, BAD_INPUT};

typedef struct s_lex
{
	char			*content;
	int				token;
	int				is_builtin;
	char			*hdoc_content;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lexer;

typedef struct s_pars
{
	char	*std_in;
	char	**parsed;
}	t_pars;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_tree
{
	int				type;
	t_lexer			*cmd;
	t_lexer			*redir;
	int				fd_in;
	int				fd_out;
	struct s_tree	*left;
	struct s_tree	*right;

}	t_tree;

typedef struct s_pid
{
	int	*pid_list;
	int	index;
}	t_pid;

typedef struct s_gen
{
	char	*prompt;
	int		exit_stat;
	int		status;
	int		hdoc;
	int		tracker;
	pid_t	*pids;
	t_env	*env;
	char	**paths;
	char	*home;
	t_lexer	*lex;
	t_pars	parser;
	t_tree	*ast;
	int		std_out;
	int		std_in;
	int		std_err;
	char	*str_err;
	char	**av;
}	t_gen;

//a supprimer
/*		display_func.c		*/
void	display_array(char **path);
void	display_token(t_lexer *lst_lex);

/*		minishell.c		*/
int		minishell_loop(t_gen *data);

/*===============================================================*/
/*			#display#		*/
/*		display_prompt.c		*/
void	display_prompt(t_gen *data);

/*		splitter.c		*/
void	splitter(t_gen *data);

/*		splitter_utils.c		*/
int		skip_to_next_quote(t_gen *data, int i);
int		is_in_quotes(char *str, int i);

/*===============================================================*/
/*			#error#		*/
/*		error.c		*/
void	arg_error(char *exec);
void	error(t_gen *data, int e);
void	print_error(char *m1, char *cmd, char *m2);

/*===============================================================*/
/*			#executor#		*/

/*		builtin_monitor.c		*/
int		exec_builtin(t_gen *data, t_lexer *cmd, t_tree *ast);

/*		calculate_commands.c		*/
int		calculate_commands(t_tree *ast);

/*		execute_ast.c		*/
int		execute_ast(t_gen *data, t_tree *ast, int pipe);

/*		execute_command.c		*/
int		execute_command(t_gen *data, t_tree *ast, int pipe);

/*		is_execve.c		*/
char	*is_excve(char *command, t_gen *data);

/*		redirections.c		*/
int		manage_lt2(t_lexer *redirs, t_tree *ast);
int		store_data(char *start, char *end, t_tree *ast, int quote);
int		manage_redirs(t_tree *ast);

/*		signal.c	*/
void	sig_child(void);
void	handler(int sig, siginfo_t *info, void *context);
void	receiveSIG(void);
void	sig_int(int sig);
void	sig_quit(int sig);

/*		close_pipes.c	*/
int close_pipes(t_tree *ast);

/*----------------------------------------------------------------*/
/*		#builtin#	*/

/*		cd.c	*/
t_env	*create_env(char *name, char *content);
int		ft_cd(t_gen *data, t_lexer *dir);

/*		echo.c		*/
char	*join_sep(char *s1, char *s2, char sep);
int		ft_echo(t_lexer *lex, t_tree *ast);

/*		env.c	*/
int		ft_env(t_gen *data, char *pref, t_tree *ast);

/*		exit.c	*/
int		ft_exit(t_gen *data, t_lexer *cmd);

/*		export.c	*/
int		ft_export(t_gen *data, t_lexer *cmd, t_tree *ast);
void	add_env(t_gen *data, t_env *new);

/*		pwd.c	*/
int		ft_pwd(t_tree *ast);

/*		unset.c		*/
void	free_env(t_env *env);
int		ft_unset(t_gen *data, t_lexer *cmd);

/*----------------------------------------------------------------*/
/*===============================================================*/

/*			#parsing#		*/

/*		env_vars_parsing.c		*/
void	create_paths(t_gen *data);
void	add_elem(t_gen *data, char *var_path);
void	stock_env_vars(t_gen *data, char **env);

/*		parsing_syntax.c	*/
int		check_syntax(t_lexer *lex);

/*		parsing_words.c	*/
char	*strdup_sin_quote(char *s1);
t_lexer	*get_words(t_lexer *head);

/*		token_insert_var.c	*/
int		var_size(char *src, int *src_i, t_gen *data);
int		insert_var(char *dst, char *src, int *src_i, t_gen *data);
int		real_size(char *content, t_gen *data);

/*		token_split.c	*/
char	**check_sub_words(char *cmd);

/*		token.c		*/
int		valid_e(char *content, int index);
t_lexer	*lexer(char **cmd_line, t_gen *data);
t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd, t_gen *data);

/*----------------------------------------------------------------*/
/*			#ast_monitor#		*/

/*		ast_builder.c		*/
t_tree	*build_tree1(t_lexer *lexer);
t_tree	*build_tree2(t_lexer *lexer);

/*		build_leaf_ast.c		*/
t_tree	*build_leaf(t_lexer *lexer);

/*		build_pipe_node_ast.c		*/
t_tree	*build_node(t_lexer *lex, t_lexer *head, int type);
void	cut_lexer(t_lexer *head, t_lexer *lex);

/*		create_pipes.c		*/
int		create_pipes(t_tree *ast);

/*----------------------------------------------------------------*/
/*===============================================================*/

/*			#utils#		*/

/*		clear.c		*/
void	clean_lex(t_lexer *lex);
void	clean_env(t_gen *data);
void	clean_envx(t_gen *data);
void	clean_parser(t_pars *pars);
void	clean_tree(t_tree *ast);
void	ft_free(void *ptr);
void	clean_data(t_gen *data);
void	delete_data(t_gen *data);

/*		env_utils.c	*/
char	*get_var_exist(t_gen *gen, char *var);
char	*get_env_var(t_gen *gen, char *var);
char	**env_to_child(t_env *env);

/*		getter.c	*/
t_gen	*get_data(t_gen *data);
int		get_pid(int pid);
int		get_exit_stat(int stat);

/*		print_tree.c		*/
void	structure(t_tree *root, int level );

/*		token_utils.c	*/
int		is_builtin(char *cmd);
void	quote_interpretation(char quote, int *inside);

/*	utils_1.c	*/
void	free_tab(char **tab);
int		is_empty(char *line);
int		len_int(int nb);
int		occur(char *str, char c, int nbOccur);

/*	initialise_pids.c	*/
void initialise_pids(t_gen *data, int total);

#endif
