/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:38:04 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/18 16:35:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Check if the command is a built-in */
int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

static void child(int infile, int outfile, t_tokens *tokens)
{
	int	pid;

	if (is_builtin(tokens->cmd[0]))
		return (builtin(tokens, tokens->outfile));
	if (!tokens->path || tokens->cmd[0][0] == '\0')
		return(
			(void)ft_dprintf(2, "Comand '%s' not found\n", tokens->cmd[0]));
	init_signals(true);	
	pid = fork();
	if (pid == 0)
	{
		if (!tokens->next)
			outfile = 1;
		if (tokens->infile > 0)
			infile = tokens->infile;
		if (tokens->outfile)
			outfile = tokens->outfile;
		exec(infile, outfile, tokens);
	}
}

void	execution(t_tokens *tokens, int n)
{
	int	temp;
	int	fd[2];

	if (!tokens->cmd[0])
		return ;
	temp = 0;
	while (tokens)
	{
		pipe(fd);
		child(temp, fd[1], tokens);
		close(fd[1]);
		if (temp != 0)
			close(temp);
		if (tokens->next)
			temp = fd[0];
		else
			close(fd[0]);
		tokens = tokens->next;
	}
	while (n--)
		wait(NULL);
}
