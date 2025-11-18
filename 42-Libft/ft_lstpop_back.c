/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstpop_back.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: emercier <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/18 13:29:13 by emercier       #+#    #+#                */
/*   Updated: 2025/11/18 14:08:01 by emercier       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_back(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	head = *lst;
	while (head)
	{
		if (head->next != NULL && head->next->next == NULL)
		{
			del(head->next->content);
			free(head->next);
			head->next = NULL;
			return ;
		}
		head = head->next;
	}
}
