/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:07:13 by emercier          #+#    #+#             */
/*   Updated: 2026/03/29 20:42:07 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "libft.h"

typedef struct s_gnl_state
{
	t_str_ref	*acc;
	t_str_ref	read;
	t_str_ref	found;
}	t_gnl_state;

char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
