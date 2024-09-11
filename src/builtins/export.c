/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:08 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/11 14:50:19 by muribe-l         ###   ########.fr       */
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
	{
		if (ft_strncmp(my_env[i], var, l) == 0)
			return (i);
	}
	return (i);
}

/* Changes the given env variable to the new value */
void	built_export(char *var, int fd)
{
	char	**my_env;
	int		i;

	my_env = split_cpy(my_envp(READ, NULL));
	i = filter_variable(my_env, var);
	if (i == -1)
		return (built_env(fd));
	if (i <= split_len(my_env))
	{
		free(my_env[i]);
		my_env[i] = malloc(sizeof(char) * (ft_strlen(var) + 1));
		if (!my_env[i])
			return ;
		ft_strlcpy(my_env[i], var, ft_strlen(var) + 1);
		my_envp(EDIT, my_env);
		return ;
	}
	my_env = ft_realloc(my_env, (sizeof(char *) * (split_len(my_env) + 2)));
	if (!my_env)
		return ;
	/* my_env[split_len(my_env) - 1] = malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!my_env[split_len(my_env) - 1])
		return ;
	ft_strlcpy(my_env[split_len(my_env) - 1], var, ft_strlen(var)); */
	my_env[split_len(my_env) - 1] = var;
	my_env[split_len(my_env)] = NULL;
	my_envp(EDIT, my_env);
}
