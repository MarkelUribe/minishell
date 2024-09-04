/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/04 13:20:06 by muribe-l         ###   ########.fr       */
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
int		here_doc(char *limit);
void	execution(t_tokens *tokens, int n);
char	*expand(char *line);
char	**get_cmd(char *line);
char	*get_path(char *command);
char	**get_files(char *line);
int		first_check(char *line);
int		builtin(t_tokens *tokens);

#endif //MINISHELL_H
