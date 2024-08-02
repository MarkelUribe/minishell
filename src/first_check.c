/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:33:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/02 18:26:53 by kabasolo         ###   ########.fr       */
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

static int	redir_checks(char *line, char a, char b)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i += len_for(&line[i], a);
		if (line[i] == a)
		{
			i += 1 + (line[i + 1] == a);
			if (line[i] == '\0')
				return (ft_dprintf \
			(2, "Syntax error near unexpected token 'newline'\n", line[i]));
			while (line[i] == ' ')
				i ++;
			if (line[i] == '\0')
				return (ft_dprintf \
			(2, "Syntax error near unexpected token 'newline'\n", line[i]));
			if (line[i] == a || line[i] == b || line[i] == '|')
				return (ft_dprintf \
			(2, "Syntax error near unexpected token '%c'\n", line[i]));
		}
	}
	return (0);
}

static int	pipe_checks(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i ++;
		if (line[i] == '|')
			return (ft_dprintf(2, "Syntax error near unexpected token '|'\n"));
		i += len_for(&line[i], '|');
		i += !(!line[i]);
	}
	i --;
	while (line[i] == ' ')
		i --;
	if (line[i] == '|')
		return (ft_dprintf(2, "Syntax error near unexpected token '|'\n"));
	return (0);
}

int	first_check(char *line)
{
	int	len;

	if (quote_marks(line))
		return (0);
	len = closest(line, "<>");
	if (line[len] == '<')
	{
		if (redir_checks(line, '<', '>'))
			return (0);
		if (redir_checks(line, '>', '<'))
			return (0);
	}
	else if (line[len] == '>')
	{
		if (redir_checks(line, '>', '<'))
			return (0);
		if (redir_checks(line, '<', '>'))
			return (0);
	}
	if (pipe_checks(line))
		return (0);
	return (1);
}
