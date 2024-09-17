/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:42:28 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/17 18:11:20 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Signal handler for SIGINT */
void	handle_sigint(int sig)
{
	sig = sig;
	ft_printf("\n");
	fflush(stdout);
}

/* Signal handler for SIGQUIT (Ctrl+\) */
void	handle_sigquit(int sig)
{
	sig = sig;
	fflush(stdout);
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
