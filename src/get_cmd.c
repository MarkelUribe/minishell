/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:10:22 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/18 16:54:07 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nearest(char *line, char *limits)
{
	int	i;
	int	simp;
	int	doub;

	i = 0;
	simp = 0;
	doub = 0;
	while (line[i])
	{
		simp += (line[i] == '\'') * !(doub % 2);
		doub += (line[i] == '\"') * !(simp % 2);
		if (ft_strchr(limits, line[i]) && !(simp % 2) && !(doub % 2))
			return (i);
		i ++;
	}
	return (i);
}

static char	*comand(char *line, char **envp)
{
	char	*temp;
	char	*cmd;
	int		len;

	len = nearest(line, "< >");
	temp = copy_n(line, len);
	cmd = expand(temp, envp);
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

char	**get_cmd(char *line, char **envp)
{
	char	**cmd;
	int		i;
	int		j;
	int		b;

	cmd = (char **)malloc((get_len(line) + 1) * sizeof(char *));
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
		if (!b)
			cmd[++i] = comand(&line[j], envp);
		j += nearest(&line[j], "< >");
	}
	cmd[++i] = NULL;
	return (cmd);
}
