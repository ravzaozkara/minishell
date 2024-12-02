/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:58:49 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/27 23:32:29 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*s;
	size_t	i;

	i = 0;
	if (ft_strlen(str) <= start || str[start] == 0)
		s = malloc(sizeof(char) * 1);
	else if (ft_strlen(str) - start > len)
		s = malloc(sizeof(char) * (len + 1));
	else
		s = malloc(sizeof(char) * (ft_strlen(str) - start + 1));
	if (!s || !str)
		return (NULL);
	while ((size_t)start < ft_strlen(str) && len > i)
		s[i++] = str[start++];
	s[i] = 0;
	return (s);
}
