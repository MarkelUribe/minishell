/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/18 11:58:47 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(char *line)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	char	*line;
	char	**tokens;
	int		pid;

	ft_printf("\n   Welcome to FUET BALISTÍCO 2,52€!\n\n");
	while(1)
	{
		line = readline("mini_fuet> ");
		if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
			return(free(line), 0);
		if (*line)
            add_history(line);
		tokens = tokenize(line);
		pid = fork();
		if (pid == -1)
			return (free(line), 1);
		if (pid == 0)
			child(line);
		wait(NULL);
		free(line);
	}
	return (0);
}
