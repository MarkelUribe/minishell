/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:10:22 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/01 19:45:34 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*comand(char *line)
{
	char	*temp;
	char	*cmd;
	int		len;

	len = closest(line, "< >");
	temp = copy_n(line, len);
	cmd = expand(temp);
	return (free(temp), cmd);
}

static int	get_len(char *line)
{
	int	i;
	int	b;
	int	words;

	i = 0;
	words = 0;
	while (line[i])
	{
		b = 0;
		while (line[i] == ' ' || line[i] == '<' || line[i] == '>')
		{
			if (line[i] == '<' || line[i] == '>')
				b = 1;
			i ++;
		}
		words += !b;
		while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
			i ++;
	}
	return (words);
}

static char	**nulloc(int size, int type)
{
	char	**x;
	int		i;

	x = malloc(size * type);
	i = -1;
	while (++i < size)
		x[i] = NULL;
	return (x);
}

char	**get_cmd(char *line)
{
	char	**cmd;
	int		i;
	int		j;
	int		b;

	j = get_len(line);
	cmd = (char **)nulloc(j + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (line[j])
	{
		b = 0;
		while (line[j] == ' ' || line[j] == '<' || line[j] == '>')
		{
			if (line[j] == '<' || line[j] == '>')
				b = 1;
			j ++;
		}
		if (!b && line[j])
			cmd[++i] = comand(&line[j]);
		j += closest(&line[j], "< >");
	}
	return (cmd);
}
