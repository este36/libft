/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                        :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: emercier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:52:49 by emercier          #+#    #+#             */
/*   Updated: 2025/11/28 15:29:20 by emercier       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	len;
	size_t	little_len;
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	len = ft_strlen(big);
	little_len = ft_strlen(little);
	if (little_len > len)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (j < little_len && (i + j) < len)
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	little_len = ft_strlen(little);
	if (len == 0 && little_len != 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (j < little_len && (i + j) < len)
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
