/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/17 18:37:16 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"
# include "utils.h"

//Global variable for signals
//pid_t	g_pid;

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
void	init_signals(void);

//Builtins
int     is_builtin(char *cmd);
int		builtin(t_tokens *tokens, int fd);
void	built_cd(char *dir, int fd);
void	built_pwd(int fd);
void	built_export(char *var, int fd);
void	built_env(int fd);
void	built_echo(t_tokens *token, int fd);
void	built_unset(char *var);

#endif //MINISHELL_H
