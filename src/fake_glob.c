/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:51 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/23 15:40:51 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status(int new)
{
	static int	i;
	int			n;

	n = i;
	if (new < 0)
		return (n);
	i = new;
	return (i);
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
