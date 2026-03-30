/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:56:54 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 19:06:14 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

static int	coroutines(t_rgx_ctx *ctx, uint64_t *id, t_rgx_thread	*t)
{
	int	r;

	(void)id;
	ctx->executed++;
	r = rgx_thread_exec(t);
	if (r == RGX_SUCCESS)
		ctx->ret = RGX_SUCCESS;
	else if (r == RGX_FAILURE)
		ft_hmap_delete(&t->vm->threads, (void *)&t->id);
	else if (r == RGX_MERROR)
		ctx->ret = RGX_MERROR;
	return (0);
}

static int	rgx_vm_run(t_rgx_vm *vm)
{
	t_rgx_ctx	ctx;

	while (1)
	{
		ctx.ret = -1;
		ctx.executed = 0;
		ft_hmap_iter(&vm->threads, &ctx, (t_hmap_iter_cb)coroutines);
		if (ctx.ret == RGX_SUCCESS || ctx.ret == RGX_MERROR)
			break ;
		if (ctx.executed == 0)
			break ;
	}
	return (ctx.ret);
}

bool	ft_regex_match(t_regex *r, const char *s, const size_t len)
{
	t_rgx_vm		vm;
	t_rgx_thread	main_thread;
	int				ret;

	ft_bzero(&vm, sizeof(vm));
	ft_bzero(&main_thread, sizeof(main_thread));
	vm.target.buf = (char *)s;
	vm.target.len = (size_t)len;
	vm.rgx = *r;
	if (ft_hmap_init(&vm.threads,
			256, sizeof(uint64_t), sizeof(t_rgx_thread)) != 0)
		return (false);
	vm.threads.hash_fn = rgx_thread_hash;
	vm.threads.cmp_fn = rgx_thread_cmp;
	main_thread.vm = &vm;
	main_thread.id = vm.threads_counter;
	ft_hmap_insert(&vm.threads, &vm.threads_counter, &main_thread);
	vm.threads_counter += 1;
	ret = rgx_vm_run(&vm);
	free(vm.threads.data);
	return (ret == RGX_SUCCESS);
}
