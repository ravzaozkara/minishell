/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 04:16:15 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/21 04:44:57 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == (unsigned char)c)
			return ((char *)str + x);
		else
			x++;
	}
	if ((unsigned char)c == 0)
		return ((char *)str + x);
	return (NULL);
}
