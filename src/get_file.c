/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:16:06 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/02 19:32:42 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char *line, char c)
{
	int	i;
	int	len;
	int	n;

	i = len_for(line, c);
	len = ft_strlen(line);
	n = 0;
	while (i < len)
	{
		n ++;
		while (line[i] == c)
			i ++;
		i += len_for(&line[i], c);
	}
	return (n);
}

static char	*create_it(char *line)
{
	int		i;
	char	*res;
	char	*temp;

	temp = (char *)malloc(3 * sizeof(char));
	temp[0] = line[0];
	temp[1] = ' ';
	temp[2] = '\0';
	if (line[1] == '<' || line[1] == '>')
		temp[1] = line[1];
	i = 0;
	while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
		i ++;
	temp = mod_join(temp, copy_n(&line[i], closest(&line[i], "< >\0")));
	res = expand(temp);
	free (temp);
	return (res);
}

char	**get_files(char *line)
{
	char	**res;
	int		len;
	int		n;
	int		i;

	len = get_size(line, '<') + get_size(line, '>');
	res = (char **)malloc((len + 1) * sizeof(char *));
	i = closest(line, "<>\0");
	n = -1;
	while (line[i])
	{
		res[++n] = create_it(&line[i]);
		i += (line[i] == '<' || line[i] == '>');
		i += (line[i] == '<' || line[i] == '>');
		i += closest(&line[i], "<>");
		
	}
	res[++n] = NULL;
	return (res);
}

/*
char	**get_file(char *line, char c, char **envp)
{
	char	**res;
	char	**temp_split1;
	char	**temp_split2;
	int		i;
	int		len;

	temp_split1 = mod_split(line, c);
	len = split_len(temp_split1);
	res = (char **)malloc(len * sizeof(char *));
	if (!temp_split1 || !res)
		return (split_free(temp_split1), NULL);
	i = -1;
	while (++i < len - 1)
	{
		temp_split2 = mod_split(temp_split1[i + 1], ' ');
		if (!temp_split2)
			return (split_free(temp_split1), split_free(res), NULL);
		res[i] = expand(temp_split2[0], envp);
		split_free(temp_split2);
		if (!res[i])
			return (split_free(temp_split1), NULL);
	}
	split_free(temp_split1);
	res[i] = NULL;
	return (res);
}
*/
