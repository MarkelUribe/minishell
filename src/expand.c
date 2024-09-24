/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/24 12:20:48 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	int_var(int new)
{
	static int	i;
	int			n;

	n = i;
	if (new >= 0)
		i = new;
	return (n);
}

static char	*expand_var(char *line)
{
	char	*temp;
	char	*res;
	int		i;

	int_var(0);
	if (line[0] == '?')
		return (ft_itoa(status(-1)));
	if (line[0] == '$')
		return (ft_strdup(""));
	i = 0;
	while (line[i] && ft_isalnum(line[i]))
		i ++;
	temp = (char *)malloc((i + 1) * sizeof(char ));
	temp[i] = '\0';
	ft_memcpy(temp, line, i);
	res = get_env(my_envp(READ, 0), temp);
	int_var(ft_strlen(temp) - 1);
	free(temp);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

char	*expand(char *line)
{
	char	*res;
	int		j;
	int		simp;
	int		doub;

	res = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (res);
	simp = 0;
	doub = 0;
	j = -1;
	while (line[++j])
	{
		simp += (line[j] == '\'') * !(doub % 2);
		doub += (line[j] == '\"') * !(simp % 2);
		if (line[j] == '$' && line[j + 1] && !(simp % 2))
		{
			res = mod_join(res, expand_var(&line[++j]));
			j += int_var(-1);
		}
		else if ((line[j] != '\'' && line[j] != '\"') || \
		(line[j] == '\'' && (doub % 2)) || (line[j] == '\"' && (simp % 2)))
			res = mod_join(res, stringify(line[j]));
	}
	return (mod_join(res, ft_strdup("")));
}
