/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:15:23 by emercier          #+#    #+#             */
/*   Updated: 2025/10/28 21:47:33 by emercier         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (n && ((uintptr_t)d & 7 || (uintptr_t)s & 7))
	{
		*d++ = *s++;
		n--;
	}
	while (n >= 8)
	{
		*((uint64_t *)d) = *((uint64_t *)s);
		d += 8;
		s += 8;
		n -= 8;
	}
	while (n)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	uint64_t		val;

	val = (unsigned char)c;
	val |= val << 8;
	val |= val << 16;
	val |= val << 32;
	p = s;
	while (n && ((uintptr_t)p & 7))
	{
		*p++ = (unsigned char)c;
		n--;
	}
	while (n >= 8)
	{
		*((uint64_t *)p) = val;
		p += 8;
		n -= 8;
	}
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, const size_t s_len)
{
	char	*res;

	if (s_len == 0)
		return (NULL);
	res = malloc(s_len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, s_len);
	res[s_len] = '\0';
	return (res);
}
