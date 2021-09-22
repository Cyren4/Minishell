/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:39:21 by cramdani          #+#    #+#             */
/*   Updated: 2021/09/21 21:52:01 by cramdani         ###   ########.fr       */
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