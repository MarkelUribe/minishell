/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:13 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/11 13:39:24 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change enviroment PWD value to the new directory */
/* void	change_pwd(char *new)
{
	char	**my_env;

	my_env = my_envp(READ, NULL);
} */

/* Change directory function */
void	built_cd(t_tokens *tokens, int fd)
{
	char	*direction;

	if (!tokens[0].cmd[1] || ft_strcmp(tokens[0].cmd[1], "~") == 0)
		direction = getenv("HOME");
	else
		direction = tokens[0].cmd[1];
	if (chdir(direction) != 0)
		ft_dprintf(fd, "%s\n", strerror(errno));
	printf("new: %s\n", getcwd(NULL, 0));
}
