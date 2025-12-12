/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_sprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:02:24 by emercier          #+#    #+#             */
/*   Updated: 2025/12/12 19:10:39 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_spec.h"

char	*temp_sprintf(const char *fmt, ...)
{
	static char	buf[1024];
	va_list		arg_list;
	t_dstr		dest;

	ft_bzero(&dest, sizeof(t_dstr));
	dest.cap = 1024;
	dest.buf = buf;
	va_start(arg_list, fmt);
	ft_printf_fn(write_str, &dest, fmt, &arg_list);
	va_end(arg_list);
	return (buf);
}
