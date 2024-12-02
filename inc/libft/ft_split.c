/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:39:07 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 00:13:13 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	kontrol(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	*free_str(char **ptr, int j)
{
	while (j > 0)
		free(ptr[--j]);
	free(ptr);
	return (NULL);
}

int	kelime(const char *s, char c)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			control++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (control);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		x;

	i = 0;
	x = 0;
	str = malloc(sizeof(char *) * (kelime(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		if (s[x] != c && s[x])
		{
			str[i] = ft_substr(&s[x], 0, (kontrol(&s[x], c)));
			if (!str[i++])
				return (free_str(str, i));
		}
		while (s[x] && s[x] != c)
			x++;
	}
	str[i] = 0;
	return (str);
}
