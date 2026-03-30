/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex_internals.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <emercier@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:00:37 by emercier          #+#    #+#             */
/*   Updated: 2026/03/30 17:47:10 by emercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REGEX_INTERNALS_H
# define FT_REGEX_INTERNALS_H

# include "libft.h"
# include "ft_hmap.h"
# include "ft_regex.h"

enum e_rgx_result
{
	RGX_SUCCESS,
	RGX_FAILURE,
	RGX_MERROR,
	RGX_CONTINUE,
};

enum e_rgx_op
{
	RGX_ANCHOR,
	RGX_SPLIT,
	RGX_MATCH,
	RGX_CHAR,
	RGX_CLASS,
	RGX_ANY,
	RGX_JMP
};

/*
 * bytecode for: "([0-9A-Z]|hi)\.c"
 *
 * 0: split 1, 9
 * 1: split 2, 4
 * 2: class <0-9, A-Z>
 * 3: jump 6
 * 4: char h
 * 5: char i
 * 6: char .
 * 7: char c
 * 8: match
 * 9: any
 * 10: jump 0
*/

typedef struct s_rgx_compiler
{
	t_darr		ops; // t_darr<uint8_t> (e_rgx_op or operand)
	t_str_ref	expr;
	size_t		pos;
	size_t		scope_end;
}	t_rgx_compiler;

typedef struct s_rgx_vm
{
	t_regex		rgx;
	t_hmap		threads; // t_hmap<uint64_t, t_rgx_thread>
	t_str_ref	target;
	uint64_t	threads_counter;
	bool		anchor_end;
}	t_rgx_vm;

typedef struct s_rgx_thread
{
	uint64_t	id;
	t_rgx_vm	*vm;
	size_t		pos;
	size_t		pc;
}	t_rgx_thread;

typedef int	(*t_rgx_op_fn)(t_rgx_thread*);

int	rgx_op_anchor(t_rgx_thread *t);
int	rgx_op_split(t_rgx_thread *t);
int	rgx_op_match(t_rgx_thread *t);
int	rgx_op_char(t_rgx_thread *t);
int	rgx_op_class(t_rgx_thread *t);
int	rgx_op_any(t_rgx_thread *t);
int	rgx_op_jmp(t_rgx_thread *t);

typedef union u_rgx_bitmap
{
	uint8_t		b[32];
	uint64_t	w[4];
}	t_rgx_bitmap;

void				rgx_bitmap_set(t_rgx_bitmap *bm, char c);
bool				rgx_bitmap_get(t_rgx_bitmap *bm, char c);
void				rgx_bitmap_range(t_rgx_bitmap *bm, char from, char to);

t_hmap_hash			rgx_thread_hash(void *key);
int					rgx_thread_cmp(void *tid1, void *tid2);
enum e_rgx_result	rgx_thread_exec(t_rgx_thread *t);

#endif
