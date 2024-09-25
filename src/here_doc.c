/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:46:46 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/25 17:04:41 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
		close(0);
}

static void	read_the_terminal(int fd, char *limit)
{
	char	*input;
	int		len;

	signal(SIGINT, &handle_heredoc);
	len = ft_strlen(limit);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (exit(0));
		if (ft_strncmp(input, limit, len + 1) == 0)
			return (free(input), exit(0));
		ft_dprintf(fd, input);
		ft_dprintf(fd, "\n");
		free(input);
	}
}

int	here_doc(char *limit)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		read_the_terminal(fd[1], limit);
	close(fd[1]);
	init_signals(2);
	waitpid(pid, NULL, 0);
	init_signals(0);
	return (fd[0]);
}
