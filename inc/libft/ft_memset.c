/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:33:52 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/21 17:29:16 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memset(void *b, int c, size_t len)
{
	t_uc *cpyb;
	size_t i;

	cpyb = (t_uc *)b;
	i = 0;
	while (i < len)
	{
		cpyb[i] = c;
		i++;
	}
	return ((void *)cpyb);
}
