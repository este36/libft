/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:06:19 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 19:06:31 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

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
	const enum e_rgx_op			op = t->vm->rgx.data[t->pc];

	if (op >= sizeof(ops) / sizeof(ops[0]) || ops[op] == NULL)
		return (RGX_FAILURE);
	if (op == RGX_CHAR || op == RGX_CLASS || op == RGX_ANY)
	{
		if (t->pos >= t->vm->target.len)
			return (RGX_FAILURE);
	}
	return (ops[op](t));
}

t_hmap_hash	rgx_thread_hash(void *key)
{
	const uint64_t	tid = *((uint64_t *)key);

	return ((t_hmap_hash)tid);
}

int	rgx_thread_cmp(void *tid1, void *tid2)
{
	const uint64_t	_tid1 = *((uint64_t *)tid1);
	const uint64_t	_tid2 = *((uint64_t *)tid2);

	if (_tid1 < _tid2)
		return (-1);
	if (_tid1 > _tid2)
		return (1);
	return (0);
}
