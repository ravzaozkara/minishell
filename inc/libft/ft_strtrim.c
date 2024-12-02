/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:55:03 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 02:03:39 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_control(const char *set, const char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	len;

	start = 0;
	len = ft_strlen(s1) - 1;
	while (s1[start] && ft_control(set, s1[start]))
		start++;
	while (len >= start && ft_control(set, s1[len]))
		len--;
	return (ft_substr(s1, start, len - start + 1));
}
