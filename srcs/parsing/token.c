#include "token.h"

void	quote_management(t_lexer *elem)
{
	if (elem->content[0] == '"')
		elem->quote_type = DOUBLE_Q;
	else if (elem->content[0] == '\'')
		elem->quote_type = SIMPLE_Q;
	else
		elem->quote_type = NO_Q;
	elem->token = WORD;
	//according to which quote-> replace variables 
	//trim the quotes after that
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "exit") == 0);
}
/*	return 1 si c'est une commande 0 sinon)*/
int	check_cmd(t_lexer *elem)
{
	if (is_builtin(elem->content))
	{
		elem->is_builtin = 1;
		return (1);
	} 
	return 0;
	
	//according to which quote-> replace variables 
}

int	check_type(t_lexer *elem)
{
	if (ft_strcmp(elem->content, "|") == 0)
		elem->token = PIPE;
	else if (ft_strcmp(elem->content, "<") == 0)
		elem->token = LT;
	else if (ft_strcmp(elem->content, "<<") == 0)
		elem->token = LT2;
	else if (ft_strcmp(elem->content, ">") == 0)
		elem->token = GT;
	else if (ft_strcmp(elem->content, ">>") == 0)
		elem->token = GT2;
	else if (elem->content[0] == '"' || elem->content[0] == '\'')
		quote_management(elem);
	else if (check_cmd(elem))
		elem->token = CMD;
	else
		quote_management(elem);
	return (1);
}

t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd)
{
	t_lexer *new;

	new = malloc(sizeof(t_lexer));
	new->content = ft_strdup(cmd);
	new->next = lst_elem;
	return (new);
}

t_lexer	*lexer(char **cmd_line, t_lexer *lst_elem)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		lst_elem = add_elem_lex(lst_elem, cmd_line[i]);
		check_type(lst_elem);
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
		printf("%s\t%s\t%s\t%s\n", tmp->content, g_token[tmp->token], tmp->is_builtin ? "Builtin" : "", tmp->token == WORD ? g_quote[tmp->quote_type]:"");
	}
}

{"echo", "blablabla" ,"|", "\' \'"}