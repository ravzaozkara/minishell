/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:54:16 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/21 17:42:14 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
	char *rtrn;
	int i;

	i = (int)ft_strlen(s);
	rtrn = (char *)s;
	while (i)
	{
		if (rtrn[i] == (char)c)
			return (rtrn + i);
		i--;
	}
	if (rtrn[i] == (char)c)
		return (rtrn + i);
	return (0);
}
