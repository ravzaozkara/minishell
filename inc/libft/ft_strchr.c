/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:50:55 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/19 17:31:04 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strchr(const char *s, int c)
{
	char *rtrn;
	int i;

	i = 0;
	rtrn = (char *)s;
	while (rtrn[i])
	{
		if (rtrn[i] == (char)c)
			return (rtrn + i);
		i++;
	}
	if (rtrn[i] == (char)c)
		return (rtrn + i);
	return (0);
}
