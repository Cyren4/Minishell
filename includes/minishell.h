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

typedef struct s_data
{
	int		status;
	char	*line;

}	t_data;

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
