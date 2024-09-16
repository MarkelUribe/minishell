/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:59 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/16 17:01:07 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_n_words(t_tokens *token)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (!ft_strcmp(token[0].cmd[1], "-n"))
		i = 1;
	while (token[0].cmd[++i])
		n++;
	return (n);
}

/* Prints string ignoring the slash */
static void	print_anti_slash(int fd, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != 92)
			write(fd, &s[i], 1);
}

/* Takes all the parameters and builds a single string */
void	print_params(t_tokens *token, int n, int fd)
{
	int		i;

	i = 2 * (n != 0) + (n == 0);
	while (token[0].cmd[i])
	{
		print_anti_slash(fd, token[0].cmd[i]);
		if (get_n_words(token) != i - n)
			ft_dprintf(fd, " ");
		i++;
	}
	if (!n)
		ft_dprintf(fd, "\n");
}

/* Echo function prints whats given */
void	built_echo(t_tokens *token, int fd)
{
	if (!token[0].cmd[1])
	{
		ft_dprintf(fd, "\n");
		return ;
	}
	if (!ft_strcmp(token[0].cmd[1], "-n"))
		print_params(token, 1, fd);
	else
		print_params(token, 0, fd);
}
