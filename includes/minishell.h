/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/18 16:48:59 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"
# include "utils.h"

//Fake global vars
char	*status(int new);
char	**my_envp(int mood, char **envp);

//Program
void	michel(char *line);
int		first_check(char *line);
char	*expand(char *line, char **envp);
char	**get_cmd(char *line, char **envp);
char	*get_path(char *command, char **envp);
char	**get_file(char *line, char c, char **envp);

#endif //MINISHELL_H
