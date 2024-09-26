/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/26 15:29:33 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrl_c;

static void	welcome_message(char **envp)
{
	char	*temp;

	temp = get_env(envp, "USER");
	ft_dprintf(1,
		"🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭\n");
	ft_dprintf(1, "🌭\t\t\t\t\t\t\t🌭\n");
	ft_dprintf(1,
		"\033[34m🌭\tWelcome to \033[31mFuet balístico 2,52€"
		"\033[34m %s🐖\033[0m\t🌭\n",
		temp);
	ft_dprintf(1, "🌭\t\t\t\t\t\t\t🌭\n");
	ft_dprintf(1,
		"🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭\n\n");
	free(temp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	status(0);
	my_envp(EDIT, split_cpy(envp));
	line = ft_strdup(" ");
	using_history();
	welcome_message(envp);
	while (line)
	{
		g_ctrl_c = 0;
		free(line);
		init_signals(0);
		line = readline("\x1b[33mmini_fuet$>\033[0m ");
		if (line && !blank(line))
			if (michel(line))
				return (my_envp(FREE, 0), free(line), status(-1));
	}
	my_envp(FREE, 0);
	if (line)
		free(line);
	ft_printf("exit\n");
	return (status(-1));
}
