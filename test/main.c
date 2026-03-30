/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:05:07 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 13:41:43 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex.h"
#include "ft_printf.h"
#include "ft_regex_internals.h"

// ^a[bc]d$
t_regex	get_bytecode(void)
{
	static uint8_t	bt[] = {
		RGX_CHAR, 'a',
		RGX_CLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		RGX_CHAR, 'd',
		RGX_ANCHOR
	};
	static t_rgx_bitmap	bm = {0};

	rgx_bitmap_set(&bm, 'b');
	rgx_bitmap_set(&bm, 'c');
	ft_memcpy(bt + 3, &bm, sizeof(bm));
	return ((t_regex)&bt);
}

int	main(int argc, char **argv)
{
	const t_regex	rgx = get_bytecode();
	const char		*test = "abd";

	(void)argv;
	(void)argc;
	ft_printf("result(%s): %d", test, ft_regex_match(rgx, test, sizeof(test)));
}
