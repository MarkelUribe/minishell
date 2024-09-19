/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:41:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/19 10:37:11 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_a_command(t_tokens *token)
{
	char	**cmd;
	char	*temp_path;

	token->path = get_path(token->cmd[0]);
	if (token->path || is_builtin(token->cmd[0]))
		return (1);
	temp_path = ft_strdup(token->cmd[0]);
	cmd = mod_split(token->cmd[0], '/');
	if (!cmd || !cmd[0])
		return (free(temp_path), 0);
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
	int			potato;
	struct stat	sb;

	token->cmd = get_cmd(line);
	if (!token->cmd || !token->cmd[0])
		return (1);
	if (is_a_command(token))
		return (1);
	potato = stat(token->path, &sb);
	if (potato == 0 && (sb.st_mode & S_IFMT) == S_IFDIR)
		ft_printf("bash: %s: Is a directory\n", token->cmd[0]);
	else if (
		potato != 0 && closest(token->cmd[0], "/")
		!= (int)ft_strlen(token->cmd[0]))
		ft_printf("bash: %s: No such file or directory\n", token->cmd[0]);
	else if (access(token->path, X_OK) == 0)
		return (1);
	else if (closest(token->cmd[0], "/") == (int)ft_strlen(token->cmd[0]))
		ft_printf("Command '%s' not found\n", token->cmd[0]);
	else if (closest(token->cmd[0], "/") != (int)ft_strlen(token->cmd[0]))
		ft_printf("bash: %s: Permission denied\n", token->cmd[0]);
	return (0);
}

static int	parsing_and_data(t_data *data)
{
	int			i;
	int			t_len;
	t_tokens	*node;

	t_len = split_len(data->pipe_split);
	i = -1;
	while (++i < t_len)
	{
		node = (t_tokens *)malloc(sizeof(t_tokens));
		if (!node)
			return (0);
		if (!get_files(data->pipe_split[i], node))
			return (0);
		if (!analize(data->pipe_split[i], node))
			return (0);
		add_token_back(&data->tokens, node);
	}
	return (1);
}

void	michel(char *line)
{
	t_data	data;

	data.pipe_split = mod_split(line, '|');
	data.tokens = NULL;
	add_history(line);
	if (first_check(line))
	{
		if (parsing_and_data(&data))
			execution(data.tokens, split_len(data.pipe_split));
	}
	split_free(data.pipe_split);
	free_tokens(&data.tokens);
}
