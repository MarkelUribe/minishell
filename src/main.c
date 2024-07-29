/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/29 13:13:54 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	status(0);
	my_envp(EDIT, split_cpy(envp));
	line = ft_strdup(" ");
	using_history();
	while (ft_strncmp(line, "exit", 5) != 0)
	{
		if (!line)
			return (ft_dprintf(2, "readline error\n"), my_envp(FREE, 0), 1);
		if (!blank(line))
			michel(line);
		free(line);
		line = readline("mini_fuet> ");
	}
	my_envp(FREE, 0);
	free(line);
	return (0);
}
