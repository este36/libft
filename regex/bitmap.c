/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:58:55 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 13:21:54 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

void	rgx_bitmap_range(t_rgx_bitmap *bm, char from, char to)
{
	const uint8_t	b1 = from >> 3;
	const uint8_t	b2 = to >> 3;
	const uint8_t	bit1 = from & 7;
	const uint8_t	bit2 = to & 7;
	int				i;

	if (b1 == b2)
		bm->b[b1] |= ((1 << (bit2 - bit1 + 1)) - 1) << bit1;
	else
	{
		bm->b[b1] |= 0xFF << bit1;
		i = b1 + 1;
		while (i < b2)
		{
			bm->b[i] = 0xFF;
			i++;
		}
		bm->b[b2] |= (1 << (bit2 + 1)) - 1;
	}
}

void	rgx_bitmap_set(t_rgx_bitmap *bm, char c)
{
	bm->b[c >> 3] |= (1 << (c & 7));
}

bool	rgx_bitmap_get(t_rgx_bitmap *bm, char c)
{
	return ((bm->b[c >> 3] >> (c & 7)) & 1);
}
