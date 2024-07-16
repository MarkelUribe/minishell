/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/16 13:40:40 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *status(int new)
{
	static int	i;
	int			n;

	n = i;
	if (new < 0)
		return (ft_itoa(n));
	i = new;
	return (NULL);
}

static int	is_there_any(char *line, char c)
{
	int	i;
	int	simp;
	int	doub;

	i = 0;
	simp = 0;
	doub = 0;
	while (line[i])
	{
		simp += (line[i] == '\'') * !(doub % 2);
		doub += (line[i] == '\"') * !(simp % 2);
		if (line[i] == c && !(simp % 2) && !(doub % 2))
			return (1);
		i ++;
	}
	return (0);
}

static int	red_bef(char *line, char c)
{
	int	i;
	int	simp;
	int	doub;

	if (!is_there_any(line, c) && !is_there_any(line, c))
		return (0);
	i = len_for(line, c);
	simp = 0;
	doub = 0;
	while (line[++i])
	{
		simp += (line[i] == '\'') * !(doub % 2);
		doub += (line[i] == '\"') * !(simp % 2);
		if (line[i] != ' ' && !(simp % 2) && !(doub % 2))
			break;
	}
	return (line[i] == '\0');
}

static char **get_cmd(char *line, char **envp)
{
	char	**temp;
	char	**cmd;
	int		len;
	int		i;

	temp = mod_split(line, ' ');
	len = split_len(temp);
	cmd = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	len = -1;
	cmd[++len] = expand(temp[i], envp);
	while (temp[++i])
	{
		if (!is_there_any(temp[i], '<') && !is_there_any(temp[i], '>'))
		{
			if (!red_bef(temp[i - 1], '<') && !red_bef(temp[i - 1], '>'))
				cmd[++len] = expand(temp[i], envp);
		}
	}
	cmd[++len] = NULL;
	return (split_free(temp), cmd);
}

/*
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
	while (i[1] < len && temp[i[1]])
	{
		if (!is_there_any(temp[i[1]], '<') && !is_there_any(temp[i[1]], '>'))
		{
			expan = expand(temp[i[1]], envp);
			if (expan && expan[0])
				cmd[++i[0]] = ft_strdup(expan);
			free (expan);
		}
		i[1] ++;
	}
	cmd[++i[0]] = NULL;
	return (split_free(temp), cmd);
}
*/

static char	**get_file(char *line, char **envp, char c)
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
		ft_printf("File: %c %s\n", c, res[i]);
	}
	split_free(temp_split1);
	res[i] = NULL;
	return (res);
}
/*
static char	**get_outfile(char *line, char *envp)
{

	return (0);
}
*/

static t_tokens	*analize(char *line, char **envp)
{
	t_tokens	*token;
	int			i;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->cmd = get_cmd(line, envp);
	ft_printf("Comand: %s\n", token->cmd[0]);
	i = 0;
	while (token->cmd[++i])
		ft_printf("Arg[%d]: %s\n", i, token->cmd[i]);
	token->path = get_path(token->cmd[0], envp);
	if (token->path)
		ft_printf("Path: %s\n", token->path);
	token->infile = get_file(line, envp, '<');
	token->outfile = get_file(line, envp, '>');
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

	status(42);
	if (argc)
		argc = 0;
	if (argv)
		argv = NULL;
	//data = {0, split_cpy(envp), NULL, NULL};
	data.my_envp = split_cpy(envp);
	if (!data.my_envp)
		return (1);
	data.tokens = NULL;
	line = readline("mini_fuet> ");
	while (ft_strncmp(line, "exit", 5) != 0)
	{
		if (line && !blank(line))
		{
			data.pipe_split = mod_split(line, '|');
			add_history(line);
			if (first_check(line))
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
