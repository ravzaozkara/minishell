/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 04:47:46 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 00:31:42 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	x;
	int		control;

	x = 0;
	control = -1;
	if ((unsigned char)c == 0)
		return ((char *)str + ft_strlen(str));
	while (str[x])
	{
		if (str[x] == (unsigned char)c)
		{
			control = x;
			x++;
		}
		else
			x++;
	}
	if (control >= 0)
		return ((char *)str + control);
	return (NULL);
}
