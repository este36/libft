/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:13:00 by emercier          #+#    #+#             */
/*   Updated: 2025/12/16 15:03:26 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdalign.h>

t_hmap_hash	str_ref_hash(t_str_ref *key)
{
	t_hmap_hash	hash;
	size_t		i;

	i = 0;
	hash = 5381;
	while (i < key->len)
	{
		hash = ((hash << 5) + hash) + (uint8_t)key->buf[i];
		i++;
	}
	return (hash);
}

int	ft_hmap_insert(t_hmap *h, void *key, void *val)
{
	size_t		slot_index;
	size_t		i;
	t_hmap_hash	hash;

	hash = h->hash_fn(key);
	slot_index = hash % h->capacity;
	hash |= 2;
	i = 0;
	while (i < h->capacity)
	{
		slot_index = (slot_index + i) % h->capacity;
		if (*(t_hmap_hash *)(h->data + slot_index * h->slot_size
			+ h->hash_off) == HMAP_SLOT_EMPTY)
		{
			ft_memcpy(h->data + slot_index * h->slot_size + h->hash_off,
				&hash, sizeof(t_hmap_hash));
			ft_memcpy(h->data + slot_index * h->slot_size + h->key_off,
				key, h->key_size);
			ft_memcpy(h->data + slot_index * h->slot_size + h->val_off,
				val, h->val_size);
			return (0);
		}
		i++;
	}
	return (-1);
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
	h->hash_fn = (t_hmap_hash_fn)str_ref_hash;
	h->cmp_fn = (t_hmap_cmp_fn)str_ref_eq;
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
