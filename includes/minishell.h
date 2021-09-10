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
	struct s_lex	*next;
}	t_lexer;

typedef struct s_gen
{
	
	int status;
	int show_prompt;
	char *std_in;
	t_lexer	*lex;
	char **parse;
	int *is_quote;
	// t_exec exec;
}	t_gen;

/*			#Parsing#		*/
//lexer

//parser
//Binary tree


/*			#Executor#		*/

// display/
/*		display.c	*/
void display_prompt(t_gen *data);

// error/
/*		error.c		*/
void	arg_error(char  *exec);

// exec/
/*		exec.c		*/
void set_vars(t_gen *mini);


#endif
