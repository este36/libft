/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstpop_front.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: emercier <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/18 13:25:13 by emercier       #+#    #+#                */
/*   Updated: 2025/11/18 14:07:50 by emercier       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_front(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	next = (*lst)->next;
	del((*lst)->content);
	free(*lst);
}
