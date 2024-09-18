/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:42:28 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/18 12:33:01 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_echo_ctrl_c(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

static void	handle_true(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

static void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	init_signals(bool flag)
{
	if (flag)
	{
		signal(SIGINT, &handle_true);
		signal(SIGQUIT, &handler_false);
	}
	else if (!flag)
	{
		signal(SIGINT, &handler_false);
		signal(SIGQUIT, SIG_IGN);
	}
}
