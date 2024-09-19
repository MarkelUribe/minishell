/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 11:10:17 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	welcome_message(char **envp)
{
	ft_dprintf(1,
	"🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭\n");
	ft_dprintf(1, "🌭\t\t\t\t\t\t\t🌭\n");
	ft_dprintf(1,
		"\033[34m🌭\tWelcome to \033[31mFuet balístico 2,52€"
		"\033[34m %s🐖\033[0m\t🌭\n",
		get_env(envp, "USER"));
	ft_dprintf(1, "🌭\t\t\t\t\t\t\t🌭\n");
	ft_dprintf(1,
	"🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭🌭\n\n");
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
	disable_echo_ctrl_c();
	welcome_message(envp);
	while (line && ft_strncmp(line, "exit", 5) != 0)
	{
		if (!blank(line))
			michel(line);
		free(line);
		init_signals(false);
		line = readline("🌭mini_fuet> ");
	}
	my_envp(FREE, 0);
	if (line)
		free(line);
	return (0);
}
