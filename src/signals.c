/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:42:28 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/25 16:31:26 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If the program isn't interactive ctrl-c doesn't work*/
static void	handle_true(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

static void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		status(130);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/* If the program is interactive acivates the ctrl-c and ctrl-\ */
static void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		status(130);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/* Calls functions depending on the programs interactivity */
void	init_signals(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, &handler_false);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 1)
	{
		signal(SIGINT, &handle_true);
		signal(SIGQUIT, &handler_false);
	}
	else if (flag == 2)
	{
		signal(SIGINT, &handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
