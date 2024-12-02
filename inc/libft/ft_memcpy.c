/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:38:44 by doaltin           #+#    #+#             */
/*   Updated: 2024/01/18 19:23:22 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;

	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (!src && !dest)
		return (dest);
	while (n > 0)
	{
		*destination++ = *source++;
		n--;
	}
	return (dest);
}
