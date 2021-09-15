#include "token.h"
// #include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "exit") == 0);
}

char	*getVar(t_gen *gen, char *var)
{
	t_env *tmp_env;
	
	tmp_env = gen->env; 

	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, var) == 0)
			return (tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return ("");
}

/*	return 1 si c'est une commande 0 sinon)*/
int	check_cmd(t_lexer *elem)
{
	char **path;

	if (is_builtin(elem->content))
	{
		elem->is_builtin = 1;
		return (1);
	} else if (ft_strncmp(elem->content, "./", 2) == 0)
		return (1);
	path = ft_split(getenv("PATH"), ':');
	
	return 0;
	//according to which quote-> replace variables 
}

void	quote_interpretation(char quote, int *inside)
{
	if (quote == '"' && *inside == NO_Q)
		*inside = DOUBLE_Q;
	else if (quote == '\'' && *inside == NO_Q)
		*inside = SIMPLE_Q;
	else if (quote == '\'' && *inside == SIMPLE_Q)
		*inside = NO_Q;
	else if (quote == '\"' && *inside == DOUBLE_Q)
		*inside = NO_Q;
}

char	*supress_char(char *str, int place)
{
	char	*new;
	int		i;
	int		decal;

	new = malloc(sizeof(char) * (ft_strlen(str)));
	decal = 0;
	while (str[i])
	{
		if (i == place)
			decal = 1;
		new[i] = str[i + decal];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

char	*replace(char *str, char *var, int start, int finish)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) - (finish - start) + ft_strlen(var)));
	while (str[i] != '$' && str[i])
	{
		new[i] = str[i];
		i++;
	}
	ft_strlcpy(new + i, var, ft_strlen(var));
	i += ft_strlen(var);
	ft_strlcpy(new + i, str + finish, ft_strlen(str) - finish + 1);
	free(str);
	return (str);
}

char	*replace_var(char *str, int place)
{
	char	var[ft_strlen(str) - place];
	int		i;

	i = 0;
	while (str[place + i])
	{
		if (ft_isspace(str[place + i]))
			break;
		var[i] = str[place + i];
		i++;
	}
	var[i] = '\0';
	return (replace(str, getVar(var), place, i))
}

int	complexe_elem(t_lexer *elem)
{
	int i;
	int	inside;

	i = 0;
	inside = NO_Q;
	while (elem->content[i])
	{
		if (elem->content[i] == '\\')
			elem->content = supress_char(elem->content, i);
		else if (elem->content[i] == '\"' || elem->content[i] == '\'')
			quote_interpretation(elem->content[i], &inside);
		else if (elem->content[i] == '$' && inside != SIMPLE_Q)
			elem->content = replace_var(elem->content, i + 1);
		i++;
	}
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
	else {
		complexe_elem(elem->content);
		elem->token = WORD;
		if (check_cmd(elem))
			elem->token = CMD;
	}
	return (1);
}
/*
if (check_cmd(elem))
		elem->token = CMD;
		*/

t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd)
{
	t_lexer *new;
	t_lexer *tmp;

	new = malloc(sizeof(t_lexer));
	new->content = ft_strdup(cmd);
	new->next = NULL;
	check_type(new);
	if (lst_elem == NULL)
		return (new);
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (lst_elem);
}

t_lexer	*lexer(char **cmd_line, t_lexer *lst_elem)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		lst_elem = add_elem_lex(lst_elem, cmd_line[i]);
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

// {"echo", "blablabla" ,"|", "\' \'"}