/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:08:03 by doaltin           #+#    #+#             */
/*   Updated: 2024/01/18 19:22:51 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num(int n)
{
	int	x;

	x = 0;
	if (n <= 0)
		x++;
	while (n)
	{
		x++;
		n /= 10;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char		*s1;
	int			i;
	long int	x;

	x = (long int)n;
	i = num(n) + 1;
	s1 = malloc(sizeof(char) * i);
	if (!s1)
		return (0);
	while (--i)
		s1[i] = 0;
	i = num(n);
	if (x == 0)
		s1[0] = 48;
	if (x < 0)
	{
		s1[0] = '-';
		x *= -1;
	}
	while (x && --i > -1)
	{
		s1[i] = x % 10 + 48;
		x = x / 10;
	}
	return (s1);
}
