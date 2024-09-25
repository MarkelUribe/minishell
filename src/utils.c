/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:48 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/24 19:08:50 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	closest(char *line, char *limits)
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
		if (ft_strchr(limits, line[i]) && !(simp % 2) && !(doub % 2))
			return (i);
	}
	return (i);
}

char	*copy_n(char *line, int n)
{
	int		i;
	char	*temp;

	temp = (char *)malloc((n + 1) * sizeof(char ));
	if (!temp)
		return (NULL);
	temp[n] = '\0';
	i = -1;
	while (++i < n)
		temp[i] = line[i];
	return (temp);
}

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

char	*mod_join(char *s1, char *s2)
{
	char	*str;
	size_t	size;

	if (!s1)
		return (free(s2), NULL);
	if (!s2)
		return (free(s1), NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char ) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	ft_strlcat(str, s2, size);
	free(s1);
	free(s2);
	s1 = NULL;
	s1 = NULL;
	return (str);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
