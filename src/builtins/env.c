/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:31 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/09 13:20:50 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env()
{
	char	**my_env;
	int		i;

	my_env = my_envp(READ, NULL);
	i = -1;
	while (my_env[++i] != NULL)
		ft_dprintf(1, "%s\n", my_env[i]);
}