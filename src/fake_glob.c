/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:51 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 16:50:32 by kabasolo         ###   ########.fr       */
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
			split_free(my_envp);
		my_envp = envp;
		return (envp);
	}
	return (NULL);
}
