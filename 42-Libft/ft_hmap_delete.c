/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:55:01 by emercier          #+#    #+#             */
/*   Updated: 2025/12/16 21:56:18 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline uint8_t	*_probe(t_hmap *h, void *key, t_hmap_hash hash)
{
	uint8_t		*slot;
	size_t		slot_index;
	t_hmap_hash	slot_hash;
	size_t		i;

	slot_index = hash % h->capacity;
	i = 0;
	while (i < h->capacity)
	{
		slot_index = (slot_index + i) % h->capacity;
		slot = h->data + (slot_index * h->slot_size);
		slot_hash = *(t_hmap_hash *)(slot + h->hash_off);
		if (slot_hash == HMAP_SLOT_EMPTY)
			return (NULL);
		if (slot_hash == hash && h->cmp_fn(slot + h->key_off, key) == 0)
			return (slot);
		i++;
	}
	return (NULL);
}

int	ft_hmap_delete(t_hmap *h, void *key)
{
	t_hmap_hash	hash;
	uint8_t		*slot;

	hash = h->hash_fn(key);
	hash |= 2;
	slot = _probe(h, key, hash);
	if (slot == NULL)
		return (-1);
	if (*(t_hmap_hash *)(slot + h->hash_off) == HMAP_SLOT_DELETED)
		return (-1);
	*(t_hmap_hash *)(slot + h->hash_off) = HMAP_SLOT_DELETED;
	return (0);
}
