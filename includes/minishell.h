/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/02 10:04:50 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <wait.h>

typedef struct s_tokens
{
	char		**command;
	char		*path;
	int			infile;
	int			outfile;
	struct s_tokens	*next;
}	t_tokens;

//Utils
int		len_for(char *line, char c);
int		first_check(char *line);
char	**mod_split(char *line, char c);

#endif //MINISHELL_H
