/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:07:13 by emercier          #+#    #+#             */
/*   Updated: 2025/10/31 15:34:47 by emercier         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_str_ref
{
	char	*buf;
	ssize_t	len;
}	t_str_ref;

typedef struct s_gnl_state
{
	t_str_ref	*acc;
	t_str_ref	read;
	t_str_ref	found;
}	t_gnl_state;

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strndup(const char *s, const size_t s_len);
void	*ft_memchr(const void *s, int c, size_t n);

char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
