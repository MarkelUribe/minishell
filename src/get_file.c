/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:16:06 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 11:01:41 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(char **files, int *fd, int i)
{
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
}

static int	*open_files(char **files)
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
			return (ft_dprintf(2, "%s: No such file or directory.\n",
					&files[i][2]), free(fd), NULL);
		if (fd[1] < 0)
			return (ft_dprintf(2, "%s: Could not be created.\n",
					&files[i][2]), free(fd), NULL);
		close_fd(files, fd, i);
		i ++;
	}
	return (fd);
}

int	get_files(char *line, t_tokens *node)
{
	char	**res;
	int		len;
	int		n;
	int		i;
	int		*fd;

	len = get_size(line, '<') + get_size(line, '>');
	res = (char **)malloc((len + 1) * sizeof(char *));
	i = closest(line, "<>\0");
	n = -1;
	while (line[i])
	{
		res[++n] = create_it(&line[i]);
		i += (line[i] == '<' || line[i] == '>');
		i += (line[i] == '<' || line[i] == '>');
		i += closest(&line[i], "<>");
	}
	res[++n] = NULL;
	fd = open_files(res);
	if (!fd)
		return (0);
	node->infile = fd[0];
	node->outfile = fd[1];
	return (free(fd), 1);
}

/*
char	**get_file(char *line, char c, char **envp)
{
	char	**res;
	char	**temp_split1;
	char	**temp_split2;
	int		i;
	int		len;

	temp_split1 = mod_split(line, c);
	len = split_len(temp_split1);
	res = (char **)malloc(len * sizeof(char *));
	if (!temp_split1 || !res)
		return (split_free(temp_split1), NULL);
	i = -1;
	while (++i < len - 1)
	{
		temp_split2 = mod_split(temp_split1[i + 1], ' ');
		if (!temp_split2)
			return (split_free(temp_split1), split_free(res), NULL);
		res[i] = expand(temp_split2[0], envp);
		split_free(temp_split2);
		if (!res[i])
			return (split_free(temp_split1), NULL);
	}
	split_free(temp_split1);
	res[i] = NULL;
	return (res);
}
*/
