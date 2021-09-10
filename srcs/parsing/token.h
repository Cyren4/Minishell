#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include "../../lib/header_lib.h"

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


#endif
