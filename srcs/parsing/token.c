#include "token.h"
#include "../../includes/minishell.h"

/*	return 1 si c'est une commande du path 0 sinon)*/
int	check_cmd(t_lexer *elem)
{
	char **path;

	if (is_builtin(elem->content))
	{
		elem->is_builtin = 1;
		return (1);
	} else if (ft_strncmp(elem->content, "./", 2) == 0)
		return (1);
	// path = ft_split(getenv("PATH"), ':');
	
	return 0;
	//according to which quote-> replace variables 
}

int	var_size(char *src, int *src_i, t_gen *data)
{
	char	env_var[ft_strlen(src) - *src_i];
	int		i;
	int		var_size;

	i = 0;
	*src_i++;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i++;
		i++;
	}
	env_var[i] = '\0';
	return (ft_strlen(get_env_var(env_var, data)));
}

int	real_size(char *content, t_gen *data)
{
	int		total_size;
	int		inside;
	int		i;

	i = 0;
	inside = NO_Q;
	total_size = 0;
	while (content[i])
	{
		if (content[i] == '\"' || content[i] == '\'')
			quote_interpretation(content[i], &inside);
		else if (content[i] == '$' && inside != SIMPLE_Q)
		{
			total_size += var_size(content, &i, data);
			continue ;
		}
		else
			total_size++;
		i++;
	}
	return (total_size);

}

int	insert_var(char *dst, char *src, int *src_i, t_gen *data)
{
	char	env_var[ft_strlen(src) - *src_i];
	int		i;
	int		var_size;

	i = 0;
	*src_i++;
	while (src[*src_i] && (ft_isalnum(src[*src_i]) || src[*src_i] == '_'))
	{
		env_var[i] = src[*src_i];
		*src_i++;
		i++;
	}
	env_var[i] = '\0';
	var_size = ft_strlen(get_env_var(env_var, data));
	ft_strlcpy(dst, get_env_var(env_var, data), var_size);
	return (var_size);
}

int	complexe_elem(t_lexer *elem, t_gen *data)
{
	char	*real_content;
	int		elem_i;
	int		i;
	int		inside;

	i = 0;
	elem_i = 0;
	inside = NO_Q;
	real_content = malloc(sizeof(char) * real_size(elem->content, data));
	while (elem->content[elem_i])
	{
		if (elem->content[i] == '\"' || elem->content[i] == '\'')
			quote_interpretation(elem->content[i], &inside);
		else if (elem->content[i] == '$' && inside != SIMPLE_Q)
		{
			i += insert_var(real_content + i, elem->content, &elem_i, data);
			continue ;
		}
		else
			real_content[i] = elem->content[elem_i];
		i++;
		elem_i++;
	}
	real_content[i] = '\0';
	free(elem->content);
	elem->content = real_content;
}

int	check_type(t_lexer *elem, t_gen *data)
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
		complexe_elem(elem->content, data);
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

t_lexer	*add_elem_lex(t_lexer *lst_elem, char *cmd, t_gen *data)
{
	t_lexer *new;
	t_lexer *tmp;

	new = malloc(sizeof(t_lexer)); //protect malloc
	if (!new)
		return (NULL);
	new->content = ft_strdup(cmd);
	new->next = NULL;
	check_type(new, data);
	if (lst_elem == NULL)
		return (new);
	tmp = lst_elem;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (lst_elem);
}

t_lexer	*lexer(char **cmd_line, t_gen *data)
{
	t_lexer *lst_elem;
	int	i;

	lst_elem = NULL;
	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (add_elem_lex(lst_elem, cmd_line[i], data) == NULL)
			printf("Error\n");
		i++;
	}
	return (lst_elem);
}

int main(int ac, char **av)
{
	t_lexer *lst_lex;
	t_gen	*data;
	(void)ac;

	lst_lex = lexer(av + 1, data);
	for (t_lexer *tmp = lst_lex; tmp; tmp = tmp->next)
	{
		printf("%s\t%s\t%s\t%s\n", tmp->content, g_token[tmp->token], tmp->is_builtin ? "Builtin" : "", tmp->token == WORD ? g_quote[tmp->quote_type]:"");
	}
}
