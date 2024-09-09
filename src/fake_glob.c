/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:51 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/09 18:47:10 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*status(int new)
{
	static int	i;
	int			n;

	n = i;
	if (new < 0)
		return (ft_itoa(n));
	i = new;
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
}

char	**my_envp(int mood, char **envp)
{
	static char	**my_envp;

	if (mood == READ)
		return (my_envp);
	if (mood == FREE)
		split_free(my_envp);
	if (mood == EDIT)
	{
		if (my_envp)
			free_split(my_envp);
		my_envp = envp;
		return (envp);
	}
	return (NULL);
}
