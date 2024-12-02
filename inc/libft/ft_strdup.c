/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:03:06 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/27 21:57:28 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*s;

	s = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, str, ft_strlen(str) + 1);
	return (s);
}
