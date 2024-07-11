/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/11 19:48:44 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_cmd(char *line, char **envp)
{
	char	**temp;
	char	**cmd;
	char 	*expan;
	int		len;
	int		i[2];
	
	temp = mod_split(line, ' ');
	len = split_len(temp);
	cmd = (char **)malloc((len + 1) * sizeof(char *));
	i[0] = -1;
	i[1] = 0;
	while (i[1] < len && temp[i[1]] && len_for(temp[i[1]], '<') < 0 && len_for(temp[i[1]], '>') < 0)
	{
		expan = expand(temp[i[1]], envp);
		if (expan && expan[0])
			cmd[++i[0]] = ft_strdup(expan);
		free (expan);
		i[1] ++;
	}
	cmd[++i[0]] = NULL;
	return (split_free(temp), cmd);
}
/*
static int	get_infile(char *line)
{
	
}

static int	get_outfile(char *line)
{
	if (line)
		return (1);
	return (0);
}
*/

static t_tokens	*analize(char *line, char **envp)
{
	t_tokens	*token;
	
	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->cmd = get_cmd(line, envp);
	token->path = get_path(token->cmd[0], envp);
	return (token);
}
/*
static int	check(t_tokens	*token)
{
	if (!token->path)
		return (ft_dprintf(2, "%s: command not found\n", token->cmd[0]));
	return (0);
}
*/
static void	once_upon_a_time(t_data *data)
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
			return ;
		add_token_back(&data->tokens, node);
	}
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
	data.my_envp = split_cpy(envp);
	if (!data.my_envp)
		return (1);
	data.pipe_split = NULL;
	data.tokens = NULL;
	line = readline("mini_fuet> ");
	while (ft_strncmp(line, "exit", 5) != 0)
	{
		if (line && !blank(line))
		{
			add_history(line);
			if (first_check(&data, line))
				once_upon_a_time(&data);
			split_free(data.pipe_split);
			free_tokens(&data.tokens);
		}
		if (line)
			free(line);
		line = readline("mini_fuet> ");
	}
	split_free(data.my_envp);
	free(line);
	return (0);
}
