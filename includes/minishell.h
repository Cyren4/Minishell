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

typedef struct s_general
{
	int show_prompt;
}	t_general;

// display/
//////////display.c
void display_prompt(t_general *mini);
////////////////////////////////////////////////////////////
// error/
////////error.c
void error(t_general *mini, int e);
///////////////////////////////////////////////////////////
// exec/
///////exec.c
void set_vars(t_general *mini);
/////////////////////////////////////////////////////////////

#endif
