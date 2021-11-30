/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:30:08 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/30 11:19:02 by cramdani         ###   ########.fr       */
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

typedef enum token
{
	PIPE,
	LT,
	LT2,
	GT,
	GT2,
	CMD,
	OPTION,
	WORD
}	t_token;

typedef enum quote
{
	NO_Q,
	SIMPLE_Q,
	DOUBLE_Q
}	t_quote;

typedef enum err
{
	QUOTES_UNCLOSED,
	BAD_MALLOC,
	BAD_INPUT
}	t_err;

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

typedef struct s_redir
{
	int		redir_count;
	int		fd_in;
	char	*start;
	char	*end;
	char	*std_in;
	int		start_flag;
	int		quote;
	char	*tmp;
}	t_redir;

typedef struct s_gen
{
	char	*prompt;
	int		exit_stat;
	int		status;
	int		tracker;
	pid_t	*pids;
	t_env	*env;
	char	**paths;
	char	*home;
	t_lexer	*lex;
	int		prev_token;
	t_pars	parser;
	t_tree	*ast;
	int		std_out;
	int		std_in;
	int		std_err;
	char	*str_err;
	char	**av;
	char	**cmd_table;
	char	*cmd;
	int		elems;
	t_redir	redirs;
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
void	clean_display(t_gen *data);

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

/*		redirections_utils.c		*/
int		valid_redir(char *cmd, t_gen *data);

/*		redirections.c		*/
char	*end_sin_quote(char *end);
void	count_redirs(t_gen *data, t_lexer *redirs);
int		check_quotes(char *end);

/*		redirections2.c		*/
void	send_data(t_gen *data, int *fd, char *start, char *end);
void	store_data(char *start, char *end, t_tree *ast, t_gen *data);
char	*expand_redir(t_gen *data, t_lexer *fd);
int		manage_lt1(t_lexer *head, t_tree *ast);
int		manage_redirs(t_tree *ast, t_gen *data);

/*		redirections3.c		*/
int		manage_lt2(t_lexer *redirs, t_tree *ast, t_gen *data);
int		r_size_herdoc(char *content, t_gen *data);
char	*expand_heredoc(char *std_in);
void	sub_send_data(t_gen *data, char *start, char *end, int i);
void	send_data_bis(t_gen *data, int *fd, char *start);

/*		signal.c	*/
void	sig_child(void);
void	receive_sig(void);
void	sig_int(int sig);

/*		close_pipes.c	*/
int		close_pipes(t_tree *ast);

/*----------------------------------------------------------------*/
/*		#builtin#	*/

/*		cd.c	*/
int		ft_cd(t_gen *data, t_lexer *dir);

/*		echo.c		*/
char	*join_sep(char *s1, char *s2, char sep);
int		ft_echo(t_lexer *lex, t_tree *ast);

/*		env.c	*/
int		ft_env(t_gen *data, t_tree *ast);
int		env_export(t_gen *data, t_tree *ast);

/*		exit_norm.c	*/
int		is_sign(char c);

/*		exit.c	*/
int		ft_exit(t_gen *data, t_lexer *cmd);

/*		export_norm.c	*/
t_env	*create_env_exp(t_gen *data, char *cmd, int eq_pos, int cat);
void	special_case(t_gen *data, t_env *new);

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

/*		expand_elem.c	*/
void	expand_norm(char *r_cont, char c, int *i);
char	*expand_elem(t_lexer *elm, t_gen *data);

/*		parsing_syntax.c	*/
int		is_redir(int token);
int		check_syntax(t_lexer *lex);

/*		parsing_words_utils.c	*/
int		nb_word(char *cmd);

/*		parsing_words.c	*/
char	**split_w(char *cmd);
char	*strdup_sin_quote(char *s1);
t_lexer	*get_words(t_lexer *head, int old_token);

/*		tild_exp_norm.c	*/
int		is_tild_exp(t_lexer *elem, t_gen *data);

/*		token_insert_var.c	*/
int		var_size(char *src, int *src_i, t_gen *data);
int		insert_var(char *dst, char *src, int *src_i, t_gen *data);
int		real_size(char *content, t_gen *data);

/*		token_split.c	*/
char	**check_sub_words(char *cmd);

/*		token_norm.c		*/
int		valid_e(char *content, int index);
int		need_interpret_quote(char c, int inside);
void	quote_interpret(char c, int *in);

/*		token.c		*/
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
void	clean_redir(t_gen *data);
void	clean_child(t_gen *data);
void	delete_data(t_gen *data);
void	clean_exit(t_gen *data);

/*		env_utils.c	*/
t_env	*create_env(char *name, char *content);
char	*get_var_exist(t_gen *gen, char *var);
char	*get_env_var(t_gen *gen, char *var);
char	**env_to_child(t_env *env);

/*		getter.c	*/
t_gen	*get_data(t_gen *data);
int		get_pid(int pid);
int		get_exit_stat(int stat);
int		calculate_len(t_lexer *cmd);

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

/*	initialise.c	*/
void	initialise_pids(t_gen *data, int total);
void	init_data(t_gen *data);

#endif
