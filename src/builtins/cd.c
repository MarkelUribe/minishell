/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:13 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 17:15:34 by muribe-l         ###   ########.fr       */
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
	free(export);
}

static char	*ft_homejoin(char *home, char *dir)
{
	char	*new;

	if (!dir || ft_strlen(dir) == 1)
		return (home);
	new = ft_strjoin(home, &dir[1]);
	free(home);
	if (!new)
		return ((void)status(MALLOC_ERROR), NULL);
	return (new);
}

/* Change directory function */
void	built_cd(char *dir, int fd)
{
	char	*export;
	char	*old;
	char	*ndir;

	old = getcwd(NULL, 0);
	if (!dir || dir[0] == '~')
		ndir = ft_homejoin(get_env(my_envp(READ, NULL), "HOME"), dir);
	else
		ndir = ft_strdup(dir);
	status(1);
	if (chdir(ndir) != 0)
		return (ft_dprintf(fd, "%s\n", strerror(errno)), free(old), free(ndir));
	free(ndir);
	ndir = getcwd(NULL, 0);
	export = malloc(sizeof(char) * (ft_strlen(ndir) + 5));
	if (!export)
		return (free(old), free(ndir), (void)status(MALLOC_ERROR));
	ft_strlcpy(export, "PWD=", 5);
	ft_strlcat(export, ndir, ft_strlen(ndir) + ft_strlen(export) + 1);
	do_export(export, fd);
	oldpwd(ndir, export, old, fd);
	free(export);
	free(old);
	free(ndir);
	status(0);
}
