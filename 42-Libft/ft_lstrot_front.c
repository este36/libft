/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstrot_front.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: emercier <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/18 13:49:41 by emercier       #+#    #+#                */
/*   Updated: 2025/11/18 14:06:09 by emercier       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrot_front(t_list **lst)
{
	t_list	*head;
	t_list	*start;

	start = *lst;
	head = *lst;
	while (head)
	{
		if (head->next != NULL && head->next->next == NULL)
		{
			*lst = start->next;
			start->next = NULL;
			head->next->next = start;
			return ;
		}
		head = head->next;
	}
}
