/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/11 19:18:01 by kabasolo         ###   ########.fr       */
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
	char		**cmd;
	char		*path;
	char		**infile;
	char		**outfile;
	int			fd_in;
	int			fd_out;
	struct s_tokens	*next;
	
}	t_tokens;

typedef struct s_data
{
	int			status_code;
	char		**my_envp;
	char		**pipe_split;
	struct s_tokens	*tokens;
	
}	t_data;

//Utils
int		len_for(char *line, char c);
void	free_tokens(t_tokens **tokens);
void	add_token_back(t_tokens **lst, t_tokens *new);
char	**mod_split(char *line, char c);
int		blank(char *line);
char	*get_env(char **envp, char *name);
char	*mod_join(char *s1, char *s2);
char	*stringify(char c);

//Program
char	*expand(char *line, char **envp);
int		first_check(t_data *data, char *line);
char	*get_path(char *command, char **envp);

#endif //MINISHELL_H
