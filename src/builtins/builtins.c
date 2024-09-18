/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:39:27 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/18 15:06:38 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if token is a built in command and executes it */
void	builtin(t_tokens *tokens, int fd)
{
	if (ft_strcmp(tokens[0].cmd[0], "cd") == 0)
		return (built_cd(tokens[0].cmd[1], fd));
	else if (ft_strcmp(tokens[0].cmd[0], "pwd") == 0)
		return (built_pwd(fd));
	else if (ft_strcmp(tokens[0].cmd[0], "export") == 0)
		return (built_export(tokens[0].cmd[1], fd));
	else if (ft_strcmp(tokens[0].cmd[0], "env") == 0)
		return (built_env(fd));
	else if (ft_strcmp(tokens[0].cmd[0], "echo") == 0)
		return (built_echo(tokens, fd));
	else if (ft_strcmp(tokens[0].cmd[0], "unset") == 0)
		return (built_unset(tokens[0].cmd[1]));
	return ;
}
