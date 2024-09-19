/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:08 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/19 17:03:55 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the length where the variable name ends with =*/
static int	var_name_len(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/* Returns the enviroment variable index especified in var */
static int	filter_variable(char **my_env, char *var)
{
	int	i;
	int	l;

	if (!var)
		return (-1);
	l = var_name_len(var);
	if (l == -1)
		return (-1);
	i = -1;
	while (my_env[++i])
		if (ft_strncmp(my_env[i], var, l) == 0)
			return (i);
	return (i);
}

/* Adds new variable in env */
static void	add_new(char **my_env, char *var)
{
	int		index;
	char	**new;

	index = split_len(my_env);
	new = malloc(sizeof(char *) * (index + 3));
	if (!new)
		return ;
	ft_memcpy(new, my_env, sizeof(char *) * index);
	new[index + 2] = NULL;
	new[index] = malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!new[index])
		return ;
	ft_strlcpy(new[index], var, ft_strlen(var) + 1);
	new[index + 1] = NULL;
	my_envp(EDIT, new);
}

/* Changes the given env variable to the new value or adds new variable */
void	built_export(char *var, int fd)
{
	char	**my_env;
	int		i;

	my_env = split_cpy(my_envp(READ, NULL));
	if (!var)
		return (split_free(my_env), built_env(fd));
	i = filter_variable(my_env, var);
	if (i == -1)
		return (split_free(my_env));
	if (i < split_len(my_env))
	{
		free(my_env[i]);
		my_env[i] = malloc(sizeof(char) * (ft_strlen(var) + 1));
		if (!my_env[i])
			return (split_free(my_env));
		ft_strlcpy(my_env[i], var, ft_strlen(var) + 1);
		my_envp(EDIT, my_env);
		return ;
	}
	add_new(my_env, var);
}
