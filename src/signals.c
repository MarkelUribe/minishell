/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:42:28 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 12:24:53 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Removes the ^C that prints when you press ctrl-c */
void	disable_echo_ctrl_c(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

/* If the program isn't interactive ctrl-c doesn't work*/
static void	handle_true(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
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
