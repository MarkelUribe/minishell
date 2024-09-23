/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:11 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 15:53:58 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pwd function, displays current directory */
void	built_pwd(int fd)
{
	char	*cwd;

	cwd = get_env(my_envp(READ, NULL), "PWD");
	if (!cwd)
		return ((void)status(MALLOC_ERROR));
	ft_dprintf(fd, "%s\n", cwd);
	free(cwd);
	status(0);
}
