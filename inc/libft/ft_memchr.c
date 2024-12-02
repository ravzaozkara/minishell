/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 05:25:14 by doaltin           #+#    #+#             */
/*   Updated: 2024/01/18 20:40:49 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *)str;
	i = 0;
	while (n > i)
	{
		if (d[i] == (unsigned char)c)
			return (d + i);
		i++;
	}
	return (0);
}
