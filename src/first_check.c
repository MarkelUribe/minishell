/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:33:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/15 16:17:25 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_marks(char *line)
{
	int	i;
	int	simp;
	int	doub;

	i = -1;
	simp = 0;
	doub = 0;
	while (line[++i])
	{
		simp += (line[i] == '\'') * !(doub % 2);
		doub += (line[i] == '\"') * !(simp % 2);
	}
	if (simp % 2)
		return (ft_dprintf(2, "Syntax error, open simple quotes \"'\".\n"), 1);
	if (doub % 2)
		return (ft_dprintf(2, "Syntax error, open double quotes '\"'.\n"), 1);
	return (0);
}

int	first_check(char *line)
{
	if (quote_marks(line))
		return (0);
	return (1);
}
/*
	data->pipe_split = (char **)malloc(2 * sizeof(char *));
	if (!data->pipe_split)
		return (0);
	data->pipe_split[0] = ft_strdup(line);
	if (!data->pipe_split[0])
		return (0);
	data->pipe_split[1] = NULL;
*/
