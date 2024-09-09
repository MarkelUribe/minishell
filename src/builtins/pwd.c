/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:11 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/09 17:36:49 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pwd function, displays current directory */
void	built_pwd()
{
	char	*cwd;

	cwd = get_env(my_envp(READ, NULL), "PWD");
	if (!cwd)
		return ;
	ft_dprintf(1, "%s\n", cwd);
	free(cwd);
}
