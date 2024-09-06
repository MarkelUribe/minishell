/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:08 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/06 12:17:32 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the length where the variable name ends */
int	var_name_len(char *env)
{
	int		i;

	i = 0;
	while(env[i] != '\0')
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

/* Returns the enviroment variable number especified in var */
int	filter_variable(char **my_env, char *var)
{
	int	i;

	if (!var)
		return (-1);
	i = -1;
	while(my_env[++i])
	{
		if (ft_strncmp(my_env[i], var, var_name_len(var)) == 0)
			return (i);
	}
	return (-1);
}

/* Changes the given env variable to the new value */
void	built_export(char *var)
{
	char	**my_env;
	int		i;

	my_env = my_envp(READ, NULL);
	i = filter_variable(my_env, var);
	if (i == -1)
		return ;
	free(my_env[i]);
	my_env[i] = malloc(sizeof(char) * ft_strlen(var) + 1);
	ft_strlcpy(my_env[i], var, ft_strlen(var));
	//my_envp(EDIT, my_env);
	//printf("%s\n", my_env[i]);
}
