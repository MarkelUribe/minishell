/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/03 12:32:21 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_cmd(char *line)
{
	
	return ()
}

static s_tokens	analize(char *line)
{
	s_tokens	*token;

	token = (s_tokens *)malloc(sizeof(s_tokens));
	if (!tokens)
		return (NULL);
	token.cmd = get_cmd(line);
	token.path = get_path(token.cmd[0]);
	token.infile = get_infile(line);
	token.outfile = get_outfile(line);
}

static int	once_upon_a_time(char *line)
{
	int			i;
	int			t_len;
	char		**all_tokens;
	s_tokens	**tokens;

	all_tokens = mod_split(line, '|');
	if (!all_tokens)
		return (1);
	t_len = split_len(all_tokens);
	tokens = (s_tokens **)malloc(t_len + 1 * sizeof(s_tokens *));
	if (!tokens)
		return (split_free(all_tokens), 1);
	tokens[t_len] == NULL;
	i = -1;
	while (++i < t_len)
	{
		tokens[i] = analize(all_tokens[i]);
		if (!tokens[i])
			return ();
	}
	split_free(all_tokens);
	return (0);
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
			once_upon_a_time(line);
		free(line);	
	}
	return (0);
}
