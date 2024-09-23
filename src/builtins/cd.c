/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:13 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 16:09:44 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change the OLD_PWD enviroment variable */
static void	oldpwd(char *dir, char *export, char *old, int fd)
{
	export = malloc(sizeof(char) * (ft_strlen(old) + 8));
	if (!export)
		return (free(old), free(dir), (void)status(MALLOC_ERROR));
	ft_strlcpy(export, "OLDPWD=", 8);
	ft_strlcat(export, old, ft_strlen(old) + ft_strlen(export) + 1);
	do_export(export, fd);
}

/* Change directory function */
void	built_cd(char *dir, int fd)
{
	char	*export;
	char	*old;

	old = getcwd(NULL, 0);
	if (!dir || ft_strcmp(dir, "~") == 0)
		dir = getenv("HOME");
	status(1);
	if (chdir(dir) != 0)
		return (ft_dprintf(fd, "%s\n", strerror(errno)), free(old));
	dir = getcwd(NULL, 0);
	export = malloc(sizeof(char) * (ft_strlen(dir) + 5));
	if (!export)
		return (free(old), free(dir), (void)status(MALLOC_ERROR));
	ft_strlcpy(export, "PWD=", 5);
	ft_strlcat(export, dir, ft_strlen(dir) + ft_strlen(export) + 1);
	do_export(export, fd);
	oldpwd(dir, export, old, fd);
	free(export);
	free(old);
	free(dir);
	status(0);
}
