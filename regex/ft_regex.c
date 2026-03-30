/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:56:54 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 18:23:07 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"

static int	coroutines(int *ret, uint64_t *id, t_rgx_thread *t)
{
	(void)id;
	*ret = rgx_thread_exec(t);
	return (*ret);
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
			64, sizeof(uint64_t), sizeof(t_rgx_thread)) != 0)
		return (false);
	vm.threads.hash_fn = rgx_thread_hash;
	vm.threads.cmp_fn = rgx_thread_cmp;
	main_thread.vm = &vm;
	ft_hmap_insert(&vm.threads, &vm.threads_counter, &main_thread);
	vm.threads_counter += 1;
	ret = -1;
	while (1)
	{
		ft_hmap_iter(&vm.threads, &ret, (t_hmap_iter_cb)coroutines);
		if (ret != RGX_CONTINUE)
			break ;
	}
	return (ret == RGX_SUCCESS);
}
