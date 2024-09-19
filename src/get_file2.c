/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:01:15 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/19 11:02:38 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char *line, char c)
{
	int	i;
	int	len;
	int	n;

	i = len_for(line, c);
	len = ft_strlen(line);
	n = 0;
	while (i < len)
	{
		n ++;
		while (line[i] == c)
			i ++;
		i += len_for(&line[i], c);
	}
	return (n);
}

char	*create_it(char *line)
{
	int		i;
	char	*res;
	char	*temp;

	temp = (char *)malloc(3 * sizeof(char));
	temp[0] = line[0];
	temp[1] = ' ';
	temp[2] = '\0';
	if (line[1] == '<' || line[1] == '>')
		temp[1] = line[1];
	i = 0;
	while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
		i ++;
	temp = mod_join(temp, copy_n(&line[i], closest(&line[i], "< >\0")));
	res = expand(temp);
	free (temp);
	return (res);
}

int	open_in(char *name)
{
	int	infile;

	if (name[0] == ' ')
		infile = open(&name[1], O_RDONLY);
	if (name[0] == '<')
		infile = here_doc(&name[1]);
	return (infile);
}

int	open_out(char *name)
{
	int	outfile;

	if (name[0] == ' ')
		outfile = open(&name[1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (name[0] == '>')
		outfile = open(&name[1], O_CREAT | O_APPEND | O_RDWR, 0644);
	return (outfile);
}
