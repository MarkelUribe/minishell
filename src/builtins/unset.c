/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:05 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/23 12:34:27 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the enviroment variable index especified in var */
static int	filter_variable(char **my_env, char *var)
{
	int	i;

	if (!var)
		return (-1);
	i = -1;
	while (my_env[++i])
		if (ft_strncmp(my_env[i], var, ft_strlen(var)) == 0)
			return (i);
	return (-1);
}

/* Unset funcition */
static void	do_unset(char *var)
{
	char	**my_env;
	int		i;

	if (!var)
		return ;
	my_env = split_cpy(my_envp(READ, NULL));
	i = filter_variable(my_env, var);
	if (i == -1)
		return ;
	free(my_env[i]);
	my_env[i] = my_env[i + 1];
	while (my_env[++i])
		my_env[i] = my_env[i + 1];
	my_env[i - 1] = NULL;
	my_envp(EDIT, split_cpy(my_env));
	free(my_env);
}

/* Loops all the variables entered to be unset */
void	built_unset(t_tokens *token)
{
	int	i;

	i = 0;
	while (token[0].cmd[++i])
		do_unset(token[0].cmd[i]);
	status(0);
}
