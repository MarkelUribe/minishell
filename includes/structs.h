/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:36:39 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/18 14:46:29 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_tokens
{
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_data
{
	char			**pipe_split;
	struct s_tokens	*tokens;
}	t_data;

#endif //STRUCTS_H