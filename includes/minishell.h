/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/23 15:51:19 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"
# include "utils.h"

//Fake global vars
int		status(int new);
char	**my_envp(int mood, char **envp);

//Program
void	michel(char *line);
int		here_doc(char *limit);
void	execution(t_tokens *tokens, int n);
char	*expand(char *line);
char	**get_cmd(char *line);
char	*get_path(char *command);
int		get_files(char *line, t_tokens *tokens);
int		first_check(char *line);

//get_file2
int		get_size(char *line, char c);
char	*create_it(char *line);
int		open_in(char *name);
int		open_out(char *name);

//Signals
void	init_signals(bool flag);
void	disable_echo_ctrl_c(void);

//Builtins
int		is_builtin(char *cmd);
void	builtin(t_tokens *tokens, int fd);
void	built_cd(char *dir, int fd);
void	built_pwd(int fd);
void	built_export(t_tokens *token, int fd);
void	do_export(char *var, int fd);
void	built_env(int fd);
void	built_echo(t_tokens *token, int fd);
void	built_unset(t_tokens *token);

#endif //MINISHELL_H
