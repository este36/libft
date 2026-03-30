/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:06:19 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 18:23:42 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

int	rgx_op_anchor(t_rgx_thread *t)
{
	if (t->vm->target.len != t->pos + 1)
		return (RGX_FAILURE);
	return (RGX_SUCCESS);
}

int	rgx_op_match(t_rgx_thread *t)
{
	(void)t;
	return (RGX_SUCCESS);
}

int	rgx_op_jmp(t_rgx_thread *t)
{
	t->pc = t->vm->rgx.data[t->pc + 1];
	return (RGX_CONTINUE);
}

enum e_rgx_result	rgx_thread_exec(t_rgx_thread *t)
{
	static const t_rgx_op_fn	ops[] = {
	[RGX_ANCHOR] = rgx_op_anchor,
	[RGX_SPLIT] = rgx_op_split,
	[RGX_MATCH] = rgx_op_match,
	[RGX_CHAR] = rgx_op_char,
	[RGX_CLASS] = rgx_op_class,
	[RGX_ANY] = rgx_op_any,
	[RGX_JMP] = rgx_op_jmp
	};

	if (t->pos >= t->vm->target.len)
		return (RGX_FAILURE);
	return (ops[t->vm->rgx.data[t->pc]](t));
}

t_hmap_hash	rgx_thread_hash(void *key)
{
	const uint64_t tid = *((uint64_t *)key);

	return ((t_hmap_hash)tid);
}

int	rgx_thread_cmp(void *tid1, void *tid2)
{
	const uint64_t _tid1 = *((uint64_t *)tid1);
	const uint64_t _tid2 = *((uint64_t *)tid2);

	return ((long long)_tid1 - (long long)_tid2);
}
