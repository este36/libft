/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_sprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:02:24 by emercier          #+#    #+#             */
/*   Updated: 2025/12/13 21:53:25 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_spec.h"

char	*temp_sprintf(const char *fmt, ...)
{
	static int	counter = 0;
	static char	buf[4][512];
	va_list		arg_list;
	t_dstr		dest;

	ft_bzero(&dest, sizeof(t_dstr));
	dest.cap = 512;
	dest.buf = buf[counter % 4];
	va_start(arg_list, fmt);
	ft_printf_fn(write_str, &dest, fmt, &arg_list);
	va_end(arg_list);
	return (buf[counter++]);
}
