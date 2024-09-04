/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:36:39 by kabasolo          #+#    #+#             */
/*   Updated: 2024/09/04 17:19:10 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_tokens
{
	char			**cmd;
	char			*path;
	char			**files;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_data
{
	char			**pipe_split;
	struct s_tokens	*tokens;
}	t_data;

#endif //STRUCTS_H