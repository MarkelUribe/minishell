/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:39:27 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/09 13:16:56 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if token is a built in command and executes it */
int	builtin(t_tokens *tokens)
{
	if (ft_strcmp(tokens[0].cmd[0], "cd") == 0)
		return (built_cd(tokens), 1);
	else if (ft_strcmp(tokens[0].cmd[0], "pwd") == 0)
		return (built_pwd(), 1);
	else if (ft_strcmp(tokens[0].cmd[0], "export") == 0)
		return (built_export(tokens[0].cmd[1]), 1);
	else if (ft_strcmp(tokens[0].cmd[0], "env") == 0)
		return (built_env(), 1);
	return (0);
}
