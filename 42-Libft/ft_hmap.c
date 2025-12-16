/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:13:00 by emercier          #+#    #+#             */
/*   Updated: 2025/12/16 01:26:15 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdalign.h>

t_hmap_hash	str_ref_hash(t_hmap *hmap, void *key)
{
	(void)hmap;
	(void)key;
	return (0);
}

int	ft_hmap_insert(t_hmap *h, void *key, void *val)
{
	(void)h;
	(void)key;
	(void)val;
	return (0);
}

void	*ft_hmap_get(t_hmap *h, void *key)
{
	(void)h;
	(void)key;
	return (NULL);
}

int	ft_hmap_init(t_hmap *h, size_t cap, size_t key_size, size_t val_size)
{
	const size_t	_a = sizeof(t_max_align);

	if (!h || cap == 0 || key_size == 0 || val_size == 0)
		return (-1);
	ft_bzero(h, sizeof(*h));
	h->hash_fn = str_ref_hash;
	h->capacity = cap;
	h->key_size = key_size;
	h->val_size = val_size;
	h->hash_off = 0;
	h->key_off = (sizeof(t_hmap_hash) + _a) & ~(_a - 1);
	h->val_off = (h->key_off + key_size + _a) & ~(_a - 1);
	h->slot_size = (h->val_off + val_size + _a) & ~(_a - 1);
	h->data = ft_calloc(cap, h->slot_size);
	if (h->data == NULL)
		return (-1);
	return (0);
}
