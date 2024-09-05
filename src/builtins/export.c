/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:08 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/05 11:55:56 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Changes the given env variable to the new value */
void built_export(char	*var)
{
    char	**my_env;

	my_env = my_envp(READ, NULL);
    while(my_env)
    {
        if (my_env)
        my_env++;
    }
}