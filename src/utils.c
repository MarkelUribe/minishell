/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:36:48 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/05 18:33:30 by kabasolo         ###   ########.fr       */
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

void	free_tokens(t_tokens **tokens)
{
	if (!tokens || !*tokens)
		return ;
	split_free((*tokens)->cmd);
	if ((*tokens)->path)
		free((*tokens)->path);
	free_tokens(&(*tokens)->next);
	free(*tokens);
	*tokens = NULL;
}

void	add_token_back(t_tokens **lst, t_tokens *new)
{
	if (*lst)
		return (add_token_back(&(*lst)->next, new));
	*lst = new;
	new->next = NULL;
}
/*

void	free_list(t_list **lst)
{
	if (!*lst)
		return ;
	free_list(&(*lst)->next);
	free (*lst);
	*lst = NULL;
}

int main()
{
	printf("%d\n", len_for("duibcujbcjef' | 'hduih|fundfj", '|'));
	return (0);
}
*/
