/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:38:04 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/25 12:12:24 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	exec(int infile, int outfile, t_tokens *tokens)
{
	if (outfile != 1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	dup2(infile, STDIN_FILENO);
	execve(tokens->path, tokens->cmd, my_envp(READ, 0));
	ft_dprintf(2, "Error: execve() failed.\n");
	exit(1);
}

static int	child(int infile, int outfile, t_tokens *tokens)
{
	int	pid;

	if (!tokens->next)
		outfile = 1;
	if (tokens->infile > 0)
		infile = tokens->infile;
	if (tokens->outfile)
		outfile = tokens->outfile;
	if (is_builtin(tokens->cmd[0]))
		return (builtin(tokens, outfile), 0);
	if (!tokens->path)
	{
		ft_dprintf(2, "%s: command not found\n", tokens->cmd[0]);
		return ((void)status(127), 0);
	}
	init_signals(1);
	pid = fork();
	if (pid == 0)
		exec(infile, outfile, tokens);
	return (pid);
}

static void	wait_childs_to_come_back_from_vietnam(int *pid, int i, int stat)
{
	if (i == 0)
		return ;
	if (pid[0] > 0)
	{
		waitpid(pid[0], &stat, 0);
		if (WIFEXITED(stat))
			status(WEXITSTATUS(stat));
	}
	wait_childs_to_come_back_from_vietnam(&pid[1], i - 1, 0);
}

void	execution(t_tokens *tokens, int n)
{
	int	i;
	int	*pid;
	int	temp;
	int	fd[2];

	if (!tokens->cmd[0] || !tokens->cmd[0][0])
		return ((void)status(0));
	pid = (int *)malloc(n * sizeof(int));
	i = -1;
	temp = 0;
	while (tokens)
	{
		pipe(fd);
		pid[++i] = child(temp, fd[1], tokens);
		close(fd[1]);
		if (temp != 0)
			close(temp);
		if (tokens->next)
			temp = fd[0];
		else
			close(fd[0]);
		tokens = tokens->next;
	}
	wait_childs_to_come_back_from_vietnam(pid, i + 1, 0);
	free(pid);
}
