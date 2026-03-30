/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:08:00 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 17:08:01 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REGEX_H
# define FT_REGEX_H

# include <stdint.h>
# include <stddef.h>
# include <libft.h>

typedef struct s_regex
{
	t_str_ref	expr;
	uint8_t		*data;
	size_t		count;
}	t_regex;

/* return -1 if a malloc failed or invalid syntax */
int		ft_regex_compile(t_regex *r, const char *rgx, const size_t len);

/* return true or false if match or not */
bool	ft_regex_match(t_regex *r, const char *s, const size_t len);

#endif
