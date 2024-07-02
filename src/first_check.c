/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:33:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/02 10:30:17 by kabasolo         ###   ########.fr       */
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
	if (simp % 2 || doub % 2)
		return (ft_dprintf(2, "Syntax error: Open quotes.\n"), 0);
	return (1);
}

static int	blank(char *line)
{
	int	i;
xdf
	i = 0;
	while (line[i] == ' ')
		i ++;
	return (!line[i]);
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

static int	pipes(char *line)
{
	int		i;
	char	**splited;

	splited = mod_split(line, '|');
	if (!splited)
		return (0);
	i = -1;
	while (splited[++i])
	{
		if (blank(splited[i]) || extra_pipe(splited[i]))
		{
			free_split(splited);
			return (ft_dprintf(2, "Syntax error: Nothing after '|'.\n"), 0);
		}
	}
	return (free_split(splited), 1);
}

int	first_check(char *line)
{
	return (quote_marks(line) && pipes(line));
}
