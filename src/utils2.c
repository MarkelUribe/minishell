/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:40:26 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/19 17:44:22 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (line[i] == ' ' || line[i] == '\t')
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

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(&envp[i][len + 1]));
	return (NULL);
}
