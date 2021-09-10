#include "token.h"

int	check_type(char *elem)
{
	if (ft_strcmp(elem, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(elem, "<") == 0)
		return (LT);
	else if (ft_strcmp(elem, "<<") == 0)
		return (LT2);
	else if (ft_strcmp(elem, ">") == 0)
		return (GT);
	else if (ft_strcmp(elem, ">>") == 0)
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

t_lexer	*lexer(char **cmd_line, t_lexer *lst_elem)
{
	int	i;
	int type;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		type = check_type(cmd_line[i]);
		lst_elem = add_elem_lex(lst_elem, type, cmd_line[i]);
		i++;
	}
	return (lst_elem);
}


int main(int ac, char **av)
{
	t_lexer *lst_lex;
	(void)ac;
	
	lst_lex = NULL;
	lst_lex = lexer(av + 1, lst_lex);
	for (t_lexer *tmp = lst_lex; tmp; tmp = tmp->next)
	{
		printf("%s\t%s\n", tmp->content, token[tmp->token]);
	}
}