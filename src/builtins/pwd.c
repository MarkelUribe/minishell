/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:11 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/11 13:39:05 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pwd function, displays current directory */
void	built_pwd(int fd)
{
	char	*cwd;

	cwd = get_env(my_envp(READ, NULL), "PWD");
	if (!cwd)
		return ;
	ft_dprintf(fd, "%s\n", cwd);
	free(cwd);
}
