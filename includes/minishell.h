/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/26 15:29:09 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"
# include "utils.h"

extern int	g_ctrl_c;

//Fake global vars
int		status(int new);
char	**my_envp(int mood, char **envp);

//Program
int		michel(char *line);
int		here_doc(char *limit);
int		execution(t_tokens *tokens, int n, int i, int temp);
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
void	init_signals(int flag);
void	disable_echo_ctrl_c(void);

//Builtins
int		is_builtin(char *cmd);
void	builtin(t_tokens *tokens, int fd);
void	built_cd(char *dir, int fd);
void	built_pwd(int fd);
void	built_export(t_tokens *token, int fd);
void	do_export(char *var, int fd, bool *error);
void	built_env(int fd);
void	built_echo(t_tokens *token, int fd);
void	built_unset(t_tokens *token);
void	built_exit(t_tokens *token);

#endif //MINISHELL_H
