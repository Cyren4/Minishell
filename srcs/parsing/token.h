#ifndef TOKEN_H
# define TOKEN_H

// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <signal.h>

# include "../../lib/header_lib.h"

# define STDIN 0

// # define WORD 0
// # define CMD 1
// # define PIPE 2 
// # define LT 3 
// # define LT2 4 
// # define GT 5 
// # define GT2 6 
// # define OPTION 7

enum e_token { WORD, CMD, PIPE, LT, LT2, GT, GT2, OPTION };
enum e_quote { NO_Q, SIMPLE_Q, DOUBLE_Q};

typedef struct s_lex
{
	char			*content;
	int				token;
	int				quote_type;
	int				is_builtin;
	struct s_lex	*next;
}	t_lexer;


/*	token_utils.c	*/
int		is_builtin(char *cmd);
void	quote_interpretation(char quote, int *inside);

/*	env_utils.c	*/
char	*get_env_var(t_gen *gen, char *var);

/*	temp to print something	*/
char *g_token[8] = {"WORD", "CMD", "PIPE", "LT", "LT2", "GT", "GT2", "OPTION"};
char *g_quote[3] = {"NO_QUOTE", "SIMPLE_QUOTE", "DOUBLE_QUOTE"};

#endif
