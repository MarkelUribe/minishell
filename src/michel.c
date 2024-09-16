/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:41:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/16 17:12:21 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*analize(char *line)
{
	t_tokens	*token;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	ft_printf("AAAAAAAAAAAAA: %s\n", line);
	token->cmd = get_cmd(line);
	if (access(token->cmd[0], F_OK | X_OK) == 0)
		token->path = ft_strdup(token->cmd[0]);
	else
		token->path = get_path(token->cmd[0]);
	token->files = get_files(line);
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
		node = analize(data->pipe_split[i]);
		if (!node)
			return ;
		add_token_back(&data->tokens, node);
	}
}

void	michel(char *line)
{
	t_data	data;

	data.pipe_split = mod_split(line, '|');
	data.tokens = NULL;
	add_history(line);
	if (first_check(line))
	{
		once_upon_a_time(&data);
		execution(data.tokens, split_len(data.pipe_split));
	}
	split_free(data.pipe_split);
	free_tokens(&data.tokens);
}
