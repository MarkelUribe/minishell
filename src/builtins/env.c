/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:31 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 12:33:59 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env(int fd)
{
	char	**my_env;
	int		i;

	my_env = my_envp(READ, NULL);
	i = -1;
	while (my_env[++i] != NULL)
		ft_dprintf(fd, "%s\n", my_env[i]);
	status(0);
}
