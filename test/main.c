/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:59:24 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 20:02:14 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex_internals.h"
#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

// "bonjour"
t_regex	*get_bytecode(void)
{
	static uint8_t	bt[] = {
		RGX_SPLIT, 3, 18,
		RGX_CHAR, 'b',
		RGX_CHAR, 'o',
		RGX_CHAR, 'n',
		RGX_CHAR, 'j',
		RGX_CHAR, 'o',
		RGX_CHAR, 'u',
		RGX_CHAR, 'r',
		RGX_MATCH,
		RGX_ANY,
		RGX_JMP, 0
	};
	static t_regex	r;

	r.expr = c_str_ref("bonjour");
	r.data = bt;
	r.count = 21;
	return (&r);
}

int	main(void)
{
	const t_regex	*r = get_bytecode();
	const char		*s = "0ajsdlaksdhjbonjour1sdkfjlskdjflj";
	bool			ret;

	ret = ft_regex_match((void *)r, (void *)s, ft_strlen(s));
	ft_printf("regex: \"%s\", target: \"%s\", result: %d\n",
		r->expr.buf, s, ret);
}
