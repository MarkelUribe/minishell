/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/08 13:37:59 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_cmd(char *line)
{
	char	**first_split;
	char	**second_split;
	char	**cmd;
	
	first_split = mod_split(line, '<');
	if (!first_split)
		return (NULL);
	if (!first_split[0])
		return (split_free(first_split), NULL);
	second_split = mod_split(first_split[0], '>');
	split_free(first_split);
	if (!second_split)
		return (NULL);
	if (!second_split[0])
		return (split_free(second_split), NULL);
	cmd = mod_split(second_split[0], ' ');
	split_free(second_split);
	return (cmd);
}

static int	get_infile(char *line)
{
	if (line)
		return (0);
	return (1);
}

static int	get_outfile(char *line)
{
	if (line)
		return (1);
	return (0);
}

static t_tokens	*analize(char *line, char **envp)
{
	t_tokens	*token;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->cmd = get_cmd(line);
	if (!token->cmd)
		return (free(token), NULL);
	token->path = get_path(token->cmd[0], envp);
	if (!token->path)
		return (free(token), NULL);
	token->infile = get_infile(line);
	if (token->infile < 0)
		return (free(token), NULL);
	token->outfile = get_outfile(line);
	if (token->outfile < 0)
		return (free(token), NULL);
	return (token);
}

static int	once_upon_a_time(t_data *data)
{
	int			i;
	int			t_len;
	t_tokens	*node;

	t_len = split_len(data->pipe_split);
	i = -1;
	while (++i < t_len)
	{
		node = analize(data->pipe_split[i], data->my_envp);
		if (!node)
			return (1);
		add_token_back(&data->tokens, node);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	
	if (argc)
		argc = 0;
	if (argv)
		argv = NULL;
	//data = {0, split_cpy(envp), NULL, NULL};
	data.status_code = 0;
	data.my_envp = split_cpy(envp);
	if (!data.my_envp)
		return (1);
	data.pipe_split = NULL;
	data.tokens = NULL;
	line = readline("mini_fuet> ");
	while (ft_strncmp(line, "exit", 5) != 0)
	{
		if (line)
		{
			add_history(line);
			if (first_check(&data, line))
				data.status_code = once_upon_a_time(&data);
			free(line);
			split_free(data.pipe_split);
			free_tokens(&data.tokens);
		}
		line = readline("mini_fuet> ");
	}
	split_free(data.my_envp);
	free(line);
	return (0);
}
