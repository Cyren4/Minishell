/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:16:33 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/20 17:28:49 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	init_data(t_gen *data)
{
	data->env = NULL;
	data->lex = NULL;
	data->parser.std_in = NULL;
	data->parser.parsed = NULL;
	data->status = 1;
}

void	clean_lex(t_lexer *lex)
{
	t_lexer *cur;
	t_lexer *next;

	if (lex == NULL)
		return ;
	cur = lex;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	clean_parser(t_pars pars)
{
	int	i;

	i = 0;
	// if (pars == NULL)
	// 	return ;
	while (pars.parsed[i])
	{
		free(pars.parsed[i]);
		i++;
	}
	free(pars.parsed);
}

void	clean_data(t_gen *data)
{
	clean_lex(data->lex);
	data->lex = NULL;
	// clean_parser(data->parser);
	// data->parser.std_in = NULL;
	// data->parser.parsed = NULL;
}

int main(int ac, char **av, char **env)
{
	t_gen	data;

	(void)av;
	if (ac != 1)
		return (0);
	init_data(&data);
	stock_env_vars(&data, env);
	while (data.status)
	{
		display_prompt(&data);
		data.lex = lexer(data.parser.parsed, &data);
		display_token(data.lex);
		clean_data(&data);
	}
	return(0);
}