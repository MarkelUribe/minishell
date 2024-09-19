/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:41:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 17:18:37 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_a_command(t_tokens *token, char *temp_path)
{
	char		**cmd;
	struct stat	sb;

	token->path = get_path(token->cmd[0]);
	if (stat(token->path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (0);
	if (token->path)
		return (1);
	temp_path = ft_strdup(token->cmd[0]);
	cmd = mod_split(token->cmd[0], '/');
	if (!cmd)
		return (free(temp_path), 0);
	if (!cmd[0])
		return (free(temp_path), free(cmd), 0);
	free(token->path);
	token->path = get_path(cmd[split_len(cmd) - 1]);
	if (token->path && ft_strcmp(token->path, temp_path) == 0)
	{
		free(token->cmd[0]);
		token->cmd[0] = ft_strdup(cmd[split_len(cmd) - 1]);
		return (split_free(cmd), free(temp_path), 1);
	}
	free(token->path);
	token->path = ft_strdup(temp_path);
	return (split_free(cmd), free(temp_path), 0);
}

int	analize(char *line, t_tokens *token)
{
	int			slash_len;
	int			cmd_len;
	int			booly;
	struct stat	sb;

	token->path = NULL;
	token->cmd = get_cmd(line);
	if (!token->cmd || !token->cmd[0] || is_builtin(token->cmd[0]))
		return (1);
	if (is_a_command(token, NULL))
		return (1);
	slash_len = closest(token->cmd[0], "/");
	cmd_len = (int)ft_strlen(token->cmd[0]);
	booly = stat(token->path, &sb);
	if (booly != 0 && slash_len != cmd_len)
		ft_printf("bash: %s: No such file or directory\n", token->cmd[0]);
	else if (booly == 0 && S_ISDIR(sb.st_mode))
		ft_printf("bash: %s: Is a directory\n", token->cmd[0]);
	else if (access(token->path, X_OK) == 0)
		return (1);
	else if (slash_len != cmd_len)
		ft_printf("bash: %s: Permission denied\n", token->cmd[0]);
	else if (token->cmd[0][0] != '\0')
		ft_printf("%s: command not found\n", token->cmd[0]);
	return (0);
}

static int	parsing_and_data(t_data *data)
{
	int			i;
	int			n;
	int			t_len;
	t_tokens	*node;

	t_len = split_len(data->pipe_split);
	i = -1;
	n = 0;
	while (++i < t_len)
	{
		node = (t_tokens *)malloc(sizeof(t_tokens));
		if (!node)
			return (0);
		n += !get_files(data->pipe_split[i], node);
		n += !analize(data->pipe_split[i], node);
		add_token_back(&data->tokens, node);
	}
	return (n);
}

void	michel(char *line)
{
	t_data	data;

	data.pipe_split = mod_split(line, '|');
	data.tokens = NULL;
	add_history(line);
	if (first_check(line))
		if (parsing_and_data(&data) == 0)
			execution(data.tokens, split_len(data.pipe_split));
	free_tokens(&data.tokens);
	split_free(data.pipe_split);
}
