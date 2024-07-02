/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/02 10:05:00 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	daddy(char *line)
{
	int		i;
	char	**splited;

	splited = mod_split(line, '|');
	if (!splited)
		return ;
	i = -1;
	while (splited[++i])
		ft_printf("%s\n", splited[i]);	
	free_split(splited);
}

int	main()
{
	char	*line;

	ft_printf("\n   Welcome to FUET BALISTÍCO 2,52€!\n\n");
	while(1)
	{
		line = readline("mini_fuet> ");
		if (!line || ft_strncmp(line, "exit", 5) == 0)
			return(free(line), 0);
        add_history(line);
		if (first_check(line))
			daddy(line);
		free(line);	
	}
	return (0);
}
