/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:01:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/10 22:22:36 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

int skip_to_next_quote(char *str, int i)
{
	char quote_type;

	quote_type = 34;
	if (str[i] == 39)
		quote_type = 39;
	i++;
	while (str[i])
	{
		if (str[i] == quote_type)
			break;
		i++; 
	}
	if (i == (int)ft_strlen(str))
		return -1;
	return i;
}

int check_quotes(char *std_in)
{
	int i;
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (std_in[i])
	{
		if (std_in[i] == '\'')
			single_q++;
		if (std_in[i] == '\"')
			double_q++;
		i++;
	}
	if ((double_q % 2 != 0) || (single_q % 2 != 0))
		return (0);
	return (1);
}

int is_in_quotes(char *str, int i)
{	
	while (i >= 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
			break;
		i--;
	}
	if (i == -1)
		return 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return i;
		i++;
	}
	return 0;
}

char **splitter(char *std_in)
{
	int i;
	int start;
	int elems;
	char **splitted;
	char **split_head;

	elems = 0;
	i = 0;
	if (!check_quotes(std_in))
		return NULL;
	while (std_in[i])
	{
		if (std_in[i] == ' ')
		{
			if (!is_in_quotes(std_in, i))
			{
				elems++;
				while (std_in[i] == ' ')
					i++;
			}
		}
		else
			i++;
	}
	elems++;
	splitted = (char **)malloc(sizeof(char *) * (elems + 1));
	split_head = splitted;
	if (!splitted)
		return NULL;
	// splitted[elems] = NULL;
	i = 0;
	std_in = ft_strtrim(std_in, " ");
	start = i;
	while (std_in[i])
	{
		if (std_in[i] == 39 || std_in[i] == 34)
			i = skip_to_next_quote(std_in, i);
		if (std_in[i] == ' ')
		{
			printf("substr: %s\n", ft_substr(std_in, start, i - start));
			*splitted = ft_substr(std_in, start, i - start);
			splitted++;
			while (std_in[i] == ' ')
				i++;
			start = i;
		}
		i++;
	}
	*splitted = ft_substr(std_in, start, i - start);
	splitted++;
	*splitted = NULL;
	return (split_head);
}

int main(int ac, char **av)
{
	int i;
	char **split;

	split = splitter(av[1]);
	(void)ac;

	i = 0;
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
}

// void display_prompt(t_gen *data)
// {
// 	// ft_putstr_fd("minishell $ ", 1);
// 	data->std_in = readline("minishell $ ");
// 	data->parse = splitter(data->std_in);
// 	data->show_prompt = 0;
// }