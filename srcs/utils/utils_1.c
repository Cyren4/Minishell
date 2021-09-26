/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:39:21 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/26 10:57:53 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    destroy_historic(t_gen *data)
{
	t_hist *cur;
	t_hist *next;

	if (data->hist == NULL)
		return;
	cur = data->hist;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}