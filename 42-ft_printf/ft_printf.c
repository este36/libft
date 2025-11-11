/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:32:23 by emercier          #+#    #+#             */
/*   Updated: 2025/11/11 12:18:43 by emercier       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_spec.h"
#include "ft_printf_ops.h"
#include <limits.h>

static bool	lookup(va_list *arg_list, t_ft_printf_spec *spec, int *print_count)
{
	static const t_ft_printf_op	ops[14] = {
		print_ptr, print_char,
		print_int, print_str,
		print_hex_upper, print_uint,
		NULL, print_int,
		print_hex_lower, print_percent,
		NULL, NULL, NULL, NULL
	};
	const t_ft_printf_op		op = ops[spec->conversion % 14];
	int							printed;

	if (!op)
		return (0);
	printed = op(arg_list, spec);
	if (printed < 0)
		return (false);
	*print_count += printed;
	return (true);
}

static int	print_safe_raw_bytes(const char **fmt, int *print_count)
{
	const char	*next_percent = ft_strchr(*fmt, '%');
	int			printed;

	if (!next_percent)
		printed = ft_strlen(*fmt);
	else
		printed = (next_percent - *fmt);
	if (write(1, *fmt, printed) < 0)
		return (false);
	*fmt += printed;
	*print_count += printed;
	return (true);
}

static int	cleanup_and_fail(va_list *arg_list)
{
	va_end(*arg_list);
	return (-1);
}

int	ft_printf(const char *fmt, ...)
{
	int					print_count;
	t_ft_printf_spec	spec;
	va_list				arg_list;

	print_count = 0;
	va_start(arg_list, fmt);
	while (*fmt)
	{
		if (!print_safe_raw_bytes(&fmt, &print_count))
			return (cleanup_and_fail(&arg_list));
		if (*fmt)
		{
			fmt++;
			parse_spec(&spec, &fmt, &arg_list);
			if (!lookup(&arg_list, &spec, &print_count))
				return (cleanup_and_fail(&arg_list));
		}
	}
	va_end(arg_list);
	return (print_count);
}
