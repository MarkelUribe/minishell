/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:41:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/18 16:55:05 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*analize(char *line, char **envp)
{
	t_tokens	*token;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->cmd = get_cmd(line, envp);
	token->path = get_path(token->cmd[0], envp);
	token->infile = get_file(line, '<', envp);
	token->outfile = get_file(line, '>', envp);
	return (token);
}

static void	once_upon_a_time(t_data *data)
{
	int			i;
	int			t_len;
	t_tokens	*node;

	t_len = split_len(data->pipe_split);
	i = -1;
	while (++i < t_len)
	{
		node = analize(data->pipe_split[i], my_envp(READ, 0));
		if (!node)
			return ;
		add_token_back(&data->tokens, node);
	}
}

static void	print_data(t_data *data)
{
	int	i;

	ft_printf("Cmd: %s\n", data->tokens->cmd[0]);
	if (data->tokens->path)
		ft_printf("Path: %s\n", data->tokens->path);
	i = 0;
	while (data->tokens->cmd[++i])
		ft_printf("Args[%d]: %s\n", i, data->tokens->cmd[i]);
	i = -1;
	while (data->tokens->infile[++i])
		ft_printf("Infiles[%d]: %s\n", i, data->tokens->infile[i]);
	i = -1;
	while (data->tokens->outfile[++i])
		ft_printf("Outfiles[%d]: %s\n", i, data->tokens->outfile[i]);
}

void	michel(char *line)
{
	t_data	data;

	data.pipe_split = mod_split(line, '|');
	data.tokens = NULL;
	add_history(line);
	if (first_check(line))
		once_upon_a_time(&data);
	print_data(&data);
	split_free(data.pipe_split);
	free_tokens(&data.tokens);
}
