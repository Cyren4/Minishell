#include "token.h"

int	check_type(char *elem)
{
	if (ft_strcmp(elem, "|"))
		return (PIPE);
	else if (ft_strcmp(elem, "<"))
		return (LT);
	else if (ft_strcmp(elem, "<<"))
		return (LT2);
	else if (ft_strcmp(elem, ">"))
		return (GT);
	else if (ft_strcmp(elem, ">>"))
		return (GT2);
	else
		return (WORD);
}

t_lexer	*add_elem_lex(t_lexer *lst_elem, int type, char *cmd)
{
	t_lexer *new;

	new = malloc(sizeof(t_lexer));
	new->content = ft_strdup(cmd);
	new->token = type;
	new->next = lst_elem;
	return (new);
}

int	lexer(char **cmd_line, t_lexer *lst_elem)
{
	int	i;
	int type;
	t_lexer *lst_lex;

	i = 0;
	lst_lex = NULL;
	while (cmd_line[i] != 0)
	{
		type = check_type(cmd_line[i]);
		lst_lex = add_elem_lex(lst_elem, type, cmd_line[i]);
		i++;
	}
}


int main(void)
{
	char exemple[256][256] = {"echo", "salut", NULL};
	
}