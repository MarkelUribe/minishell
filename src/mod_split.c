/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:37:01 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/08 13:06:25 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	len_for(char *line, char c)
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
		if (line[i] == c && !(simp % 2) && !(doub % 2))
			return (i);
		i ++;
	}
	return (-1);
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

static char	*spliting(char *line, int n)
{
	int		i;
	char	*res;
	char	*temp;

	temp = (char *)malloc((n + 1) * sizeof(char ));
	if (!temp)
		return (NULL);
	temp[n] = '\0';
	i = -1;
	while(++i < n)
		temp[i] = line[i];
	res = ft_strtrim(temp, " ");
	free(temp);
	return (res);
}

char	**mod_split(char *line, char c)
{
	int		i;
	int		len;
	int		words;
	char	**result;

	while (line[0] == c)
		line ++;
	words = count_words(line, c);
	result = (char **)malloc((words + 1) * sizeof(char *)); 
	if (!result)
		return (NULL);
	result[words] = NULL;
	i = -1;
	while (++i < words)
	{
		if (i == words - 1)
			len = ft_strlen(line);
		else
			len = len_for(line, c);
		result[i] = spliting(line, len);
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

	split = mod_split("|||||||||||ahdohduhduslhdu |dbbsud | ihiodh | hhouhf", '|');
	if (!split)
		return(ft_printf("valio verga\n"), 0);
	i = 0;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		i ++;
	}
	return (0);
}
*/
