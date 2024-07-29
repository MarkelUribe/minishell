/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:16:06 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/29 16:49:06 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
} // ARREGLAR
