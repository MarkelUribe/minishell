/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/09 17:34:06 by muribe-l         ###   ########.fr       */
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

//Builtins
int		builtin(t_tokens *tokens);
void	built_cd(t_tokens *tokens);
void	built_pwd();
void    built_export(char	*var);
void	built_env();

#endif //MINISHELL_H
