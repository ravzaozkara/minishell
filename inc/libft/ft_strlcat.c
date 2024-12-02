/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:20:59 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 14:21:04 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = -1;
	while (dest[i] && i < n)
		i++;
	while (i + j + 1 < n && src[++j])
		dest[i + j] = src[j];
	if (i < n)
		dest[i + j] = 0;
	return (i + ft_strlen(src));
}
