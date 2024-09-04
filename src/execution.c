/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:38:04 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/04 16:24:37 by muribe-l         ###   ########.fr       */
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
	if (!builtin(tokens))
	{
		execve(tokens->path, tokens->cmd, my_envp(READ, 0));
		ft_dprintf(2, "Error: execve() failed.\n");
	}
	exit(1);
}

static int	open_in(char *name)
{
	int	infile;

	if (name[0] == ' ')
		infile = open(&name[1], O_RDONLY);
	if (name[0] == '<')
		infile = here_doc(&name[1]);
	return (infile);
}

static int	open_out(char *name)
{
	int	outfile;

	if (name[0] == ' ')
		outfile = open(&name[1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (name[0] == '<')
		outfile = open(&name[1], O_CREAT | O_APPEND | O_RDWR, 0644);
	return (outfile);
}

static int *open_files(char **files)
{
	int	i;
	int	*fd;

	fd = (int *)malloc(2 * sizeof(int));
	fd[0] = 0;
	fd[1] = 0;
	i = 0;
	while (files[i])
	{
		if (files[i][0] == '<')
			fd[0] = open_in(&files[i][1]);
		if (files[i][0] == '>')
			fd[1] = open_out(&files[i][1]);
		if (fd[0] < 0)
			return (ft_dprintf(2, "%s: No such file or directory.\n", &files[i][2]), free(fd), NULL);
		if (fd[1] < 0)
			return (ft_dprintf(2, "%s: Could not be created.\n", &files[i][2]), free(fd), NULL);
		if (files[i + 1] && files[i + 1][0] == '<' && fd[0] > 0)
		{
			close(fd[0]);
			fd[0] = 0;
		}
		if (files[i + 1] && files[i + 1][0] == '>' && fd[1] > 0)
		{
			close(fd[1]);
			fd[1] = 0;
		}
		i ++;
	}
	return (fd);
}

static int	is_builtin(char *cmd)
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
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static void child(int infile, int outfile, t_tokens *tokens)
{
	int	pid;
	int	*fd;

	fd = open_files(tokens->files);
	if (!fd)
		return ;
	if ((!tokens->path || tokens->cmd[0][0] == '\0') && !is_builtin(tokens->cmd[0]))
		return(
			ft_dprintf(2, "Comand '%s' not found\n", tokens->cmd[0]), free(fd));
	pid = fork();
	if (pid == 0)
	{
		if (!tokens->next)
			outfile = 1;
		if (fd[0] > 0)
			infile = fd[0];
		if (fd[1] > 0)
			outfile = fd[1];
		exec(infile, outfile, tokens);
	}
	free(fd);
}

void	execution(t_tokens *tokens, int n)
{
	int	temp;
	int	fd[2];

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
