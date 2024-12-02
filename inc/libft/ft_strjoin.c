/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:34:43 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 12:31:11 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	x;
	char	*s;

	i = -1;
	x = -1;
	if (!s1 || !s2)
		return (NULL);
	s = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!s)
		return (0);
	while (s1[++i])
		s[i] = s1[i];
	while (s2[++x])
		s[i + x] = s2[x];
	s[i + x] = 0;
	return (s);
}
