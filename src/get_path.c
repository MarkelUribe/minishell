/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:38:21 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 16:33:18 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_command_path(char	**paths, char *command)
{
	int		i;
	char	*path_part;
	char	*command_path;

	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		if (!path_part)
			return (NULL);
		command_path = ft_strjoin(path_part, command);
		free(path_part);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free(command_path);
		i ++;
	}
	return (NULL);
}

char	*get_path(char *command)
{
	char		*command_path;
	char		*env_path;
	char		**paths;
	struct stat	sb;

	if (!command || !command[0])
		return (ft_strdup(""));
	if (stat(command, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (ft_strdup(command));
	env_path = get_env(my_envp(READ, 0), "PATH");
	if (!env_path)
		return (ft_dprintf(2, "Error: couldn't find the $PATH.\n"), NULL);
	paths = ft_split(env_path, ':');
	free (env_path);
	if (!paths)
		return (NULL);
	command_path = search_command_path(paths, command);
	split_free(paths);
	return (command_path);
}
