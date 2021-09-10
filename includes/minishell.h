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

# define WORD 0
# define CMD 1
# define PIPE 2 
# define LT 3 
# define LT2 4 
# define GT 5 
# define GT2 6 
# define OPTION 7 

typedef struct s_lex
{
	char *content;
	int token;
	t_lexer	*next;
}	t_lexer;

typedef struct s_par
{
	int		status;
	t_lexer	*lex;
	char 	**parse;
}	t_parser;

typedef struct s_gen
{
	t_parser pars;
	// t_exec exec;
}	t_gen;

/*			#Parsing#		*/
//lexer

//parser
//Binary tree


/*			#Executor#		*/

// display/
/*		display.c	*/
void display_prompt(t_data *mini);

// error/
/*		error.c		*/
void	arg_error(char  *exec);

// exec/
/*		exec.c		*/
void set_vars(t_data *mini);


#endif
