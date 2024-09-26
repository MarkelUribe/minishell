/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:55:40 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/26 12:49:30 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char	*n)
{
	int	i;

	if (n[0] == '-' && !n[1])
		return (0);
	i = -!(*n == '-');
	while (n[++i])
		if (!ft_isdigit(n[i]))
			return (0);
	return (1);
}

void	built_exit(t_tokens *token)
{
	ft_printf("exit\n");
	if (!token[0].cmd[1])
		status(0);
	else if (token[0].cmd[2])
	{
		ft_printf("exit: too many arguments\n");
		status(1);
	}
	else if (is_number(token[0].cmd[1]) && !token[0].cmd[2])
		status((unsigned char)ft_atoi(token[0].cmd[1]));
	else
	{
		ft_printf("exit: %s: numeric argument required\n",
			token[0].cmd[1]);
		status(2);
	}
}
