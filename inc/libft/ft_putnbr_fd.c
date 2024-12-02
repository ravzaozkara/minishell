/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:01:25 by doaltin           #+#    #+#             */
/*   Updated: 2023/12/28 13:28:32 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	x;

	x = (long int)n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	if (x > 9)
	{
		ft_putnbr_fd(x / 10, fd);
		ft_putchar_fd(x % 10 + 48, fd);
	}
	if (x < 10)
		ft_putchar_fd(x + 48, fd);
}
