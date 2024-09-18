/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:48 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/18 15:13:04 by kabasolo         ###   ########.fr       */
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

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(&envp[i][len + 1]));
		i ++;
	}
	return (NULL);
}

void	free_tokens(t_tokens **tokens)
{
	if (!tokens || !*tokens)
		return ;
	split_free((*tokens)->cmd);
	if ((*tokens)->path)
		free((*tokens)->path);
	free_tokens(&(*tokens)->next);
	free(*tokens);
	*tokens = NULL;
}

void	add_token_back(t_tokens **lst, t_tokens *new)
{
	if (*lst)
		return (add_token_back(&(*lst)->next, new));
	*lst = new;
	new->next = NULL;
}

int	blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i ++;
	return (!line[i]);
}

char	*stringify(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char ));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
