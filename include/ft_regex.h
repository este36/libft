/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:08:00 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 13:41:17 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REGEX_H
# define FT_REGEX_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t	*t_regex;

/* return -1 if a malloc failed or invalid syntax */
int					ft_regex_compile(t_regex r,
						const char *rgx, const size_t len);

/* return true or false if match or not */
bool				ft_regex_match(t_regex r,
						const char *s, const size_t len);

#endif
