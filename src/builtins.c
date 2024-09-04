/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:39:27 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/04 17:03:57 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change directory function */
void	built_cd(t_tokens *tokens)
{
	int	result;

	if (tokens[0].cmd[1] == NULL)
		result = chdir("/");
	else
		result = chdir(tokens[0].cmd[1]);
	if (result != 0)
		ft_dprintf(1, "%s\n", strerror(errno));
}

/* Pwd function */
void	built_pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_dprintf(1, "%s\n", cwd);
	free(cwd);
}

/* Checks if token is a built in command and executes it */
int	builtin(t_tokens *tokens)
{
	if (ft_strcmp(tokens[0].cmd[0], "cd") == 0)
		return (built_cd(tokens), 1);
	else if (ft_strcmp(tokens[0].cmd[0], "pwd") == 0)
		return (built_pwd(), 1);
	return (0);
}
