/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:28:39 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/18 16:49:55 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <wait.h>

# define RESET "\001\e[0m\002"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"

enum
{
	READ,
	EDIT,
	DEL,
	FREE,
	MEM
};

int		len_for(char *line, char c);
void	free_tokens(t_tokens **tokens);
void	add_token_back(t_tokens **lst, t_tokens *new);
char	**mod_split(char *line, char c);
int		blank(char *line);
char	*get_env(char **envp, char *name);
char	*mod_join(char *s1, char *s2);
char	*copy_n(char *line, int n);

#endif //UTILS_H