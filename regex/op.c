/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:25:40 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 19:07:53 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

int	rgx_op_split(t_rgx_thread *t)
{
	const uint64_t	tid1 = t->vm->threads_counter++;
	const uint64_t	tid2 = t->vm->threads_counter++;
	const uint64_t	my_id = t->id;
	t_rgx_thread	t1;
	t_rgx_thread	t2;

	t1 = *t;
	t2 = *t;
	t1.id = tid1;
	t1.pc = t->vm->rgx.data[t->pc + 1];
	t2.id = tid2;
	t2.pc = t->vm->rgx.data[t->pc + 2];
	if (ft_hmap_insert(&t->vm->threads, (void *)&tid1, &t1) != 0)
		return (RGX_MERROR);
	if (ft_hmap_insert(&t->vm->threads, (void *)&tid2, &t2) != 0)
		return (RGX_MERROR);
	ft_hmap_delete(&t->vm->threads, (void *)&my_id);
	return (RGX_CONTINUE);
}

int	rgx_op_char(t_rgx_thread *t)
{
	if (t->vm->rgx.data[t->pc + 1] == t->vm->target.buf[t->pos])
	{
		t->pos++;
		t->pc += 2;
		return (RGX_CONTINUE);
	}
	return (RGX_FAILURE);
}

int	rgx_op_class(t_rgx_thread *t)
{
	t_rgx_bitmap	*bm;

	bm = (void *)&t->vm->rgx.data[t->pc + 1];
	if (rgx_bitmap_get(bm, t->vm->target.buf[t->pos]))
	{
		t->pos++;
		t->pc += 1 + sizeof(*bm);
		return (RGX_CONTINUE);
	}
	return (RGX_FAILURE);
}

int	rgx_op_any(t_rgx_thread *t)
{
	if (t->pos >= t->vm->target.len)
		return (RGX_FAILURE);
	t->pos++;
	t->pc++;
	return (RGX_CONTINUE);
}
