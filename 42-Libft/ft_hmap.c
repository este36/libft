/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:13:00 by emercier          #+#    #+#             */
/*   Updated: 2025/12/16 18:38:25 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdalign.h>

static uint8_t	*hmap_probe(t_hmap *h, void *key, t_hmap_hash hash)
{
	size_t		base;
	size_t		slot;
	size_t		i;
	t_hmap_hash	slot_hash;
	uint8_t		*p;

	base = hash % h->capacity;
	i = 0;
	while (i < h->capacity)
	{
		slot = (base + i) % h->capacity;
		p = h->data + slot * h->slot_size;
		slot_hash = *(t_hmap_hash *)(p + h->hash_off);
		if (slot_hash == HMAP_SLOT_EMPTY
			|| (slot_hash == hash && h->cmp_fn(p + h->key_off, key) == 0))
			return (p);
		i++;
	}
	return (NULL);
}

int	ft_hmap_insert(t_hmap *h, void *key, void *val)
{
	t_hmap_hash	hash;
	t_hmap_hash	slot_hash;
	uint8_t		*p;

	hash = h->hash_fn(key);
	hash |= 2;
	p = hmap_probe(h, key, hash);
	if (p == NULL)
		return (-1);
	slot_hash = *(t_hmap_hash *)(p + h->hash_off);
	if (slot_hash == HMAP_SLOT_EMPTY || slot_hash == HMAP_SLOT_DELETED)
	{
		ft_memcpy(p + h->hash_off, &hash, sizeof(t_hmap_hash));
		ft_memcpy(p + h->key_off, key, h->key_size);
	}
	ft_memcpy(p + h->val_off, val, h->val_size);
	return (0);
}

int	ft_hmap_delete(t_hmap *h, void *key)
{
	t_hmap_hash	hash;
	uint8_t		*p;

	hash = h->hash_fn(key);
	hash |= 2;
	p = hmap_probe(h, key, hash);
	if (p == NULL || *(t_hmap_hash *)(p + h->hash_off) <= HMAP_SLOT_DELETED)
		return (-1);
	*(t_hmap_hash *)(p + h->hash_off) = HMAP_SLOT_DELETED;
	return (0);
}

void	*ft_hmap_get(t_hmap *h, void *key)
{
	t_hmap_hash	hash;
	t_hmap_hash	slot_hash;
	uint8_t		*p;

	hash = h->hash_fn(key);
	hash |= 2;
	p = hmap_probe(h, key, hash);
	if (p == NULL)
		return (NULL);
	slot_hash = *(t_hmap_hash *)(p + h->hash_off);
	if (slot_hash == HMAP_SLOT_EMPTY)
		return (NULL);
	return (p + h->val_off);
}

int	ft_hmap_init(t_hmap *h, size_t cap, size_t key_size, size_t val_size)
{
	const size_t	_a = sizeof(t_max_align);

	if (!h || val_size == 0)
		return (-1);
	ft_bzero(h, sizeof(*h));
	h->hash_fn = (t_hmap_hash_fn)str_ref_hash;
	h->cmp_fn = (t_hmap_cmp_fn)str_ref_cmp;
	h->capacity = cap;
	if (h->capacity == 0)
		h->capacity = 256;
	h->key_size = key_size;
	if (h->key_size == 0)
		h->key_size = sizeof(t_str_ref);
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
