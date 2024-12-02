/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 01:58:58 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/25 01:59:07 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s;
	size_t	i;
	size_t	control;

	s = (char *)haystack;
	i = 0;
	control = 0;
	if (!*needle)
		return (s);
	while (i < len && s[i])
	{
		control = 0;
		while (s[i + control] == needle[control] && i + control < len
			&& needle[control])
			control++;
		if (needle[control] == 0)
			return (s + i);
		else
			i++;
	}
	return (NULL);
}
