/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:04:47 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 19:04:58 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

int	rgx_op_anchor(t_rgx_thread *t)
{
	if (t->pos != t->vm->target.len)
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
