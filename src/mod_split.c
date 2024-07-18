/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:37:01 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/18 16:51:07 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	len_for(char *line, char c)
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
		if (line[i] == c && !(simp % 2) && !(doub % 2))
			return (i);
	}
	return (i);
}
*/

static int	count_words(char *line, char c)
{
	int	i;
	int	words;
	int	simp;
	int	doub;

	i = 0;
	words = 0;
	simp = 0;
	doub = 0;
	while (line[i] == c)
		i ++;
	while (line[i])
	{
		while (line[i] && line[i] != c)
		{
			simp += (line[i] == '\'') * !(doub % 2);
			doub += (line[i] == '\"') * !(simp % 2);
			i ++;
		}
		words += (!(simp % 2) && !(doub % 2));
		while (line[i] == c)
			i ++;
	}
	return (words);
}

char	**mod_split(char *line, char c)
{
	int		i;
	int		len;
	int		words;
	char	**result;

	words = count_words(line, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[words] = NULL;
	i = -1;
	while (++i < words)
	{
		while (line[0] == c)
			line ++;
		len = len_for(line, c);
		result[i] = copy_n(line, len);
		if (!result[i])
			return (split_free(result), NULL);
		line += len + 1;
	}
	return (result);
}
/*
int main()
{
	char **split;
	int i;

	split = mod_split("       a'aa  aaa'a     a", ' ');
	if (!split)
		return(ft_printf("valio verga\n"), 0);
	i = 0;
	while (split[i])
	{
		ft_printf(".%s.\n", split[i]);
		i ++;
	}
	return (0);
}
*/
