/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:48 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/25 19:45:58 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_for(char *line, char c)
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
			return (i);
		i ++;
	}
	return (-1);
}
/*
int main()
{
	printf("%d\n", len_for("duibcujbcjef' | 'hduih|fundfj", '|'));
	return (0);
}
*/
