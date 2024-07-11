/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:33:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/11 19:14:22 by kabasolo         ###   ########.fr       */
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

static int	extra_pipe(char *line)
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
		if (simp % 2 == 0 && doub % 2 == 0 && line[i] == '|')
			return(1);
	}
	return (0);
}

static int	pipes(char **splited, char *line)
{
	int		i;

	if (line[0] == '|')
		return (ft_dprintf(2, "Syntax error near unexpected token '|'.\n"), 0);
	if (!splited)
		return (0);
	i = -1;
	while (splited[++i])
	{
		if (blank(splited[i]) || extra_pipe(splited[i]))
			return (ft_dprintf(2, "Syntax error near unexpected token '|'.\n"), 0);
	}
	return (1);
}

int	first_check(t_data *data, char *line)
{
	if (quote_marks(line))
		return (0);
	data->pipe_split = mod_split(line, '|');
	if (!data->pipe_split)
		return (0);
	if (len_for(line, '|') > -1)
		return (pipes(data->pipe_split, line));
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
