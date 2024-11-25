/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:35:20 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/10 17:14:25 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstsize(t_list *lst)
{
	int counted;

	if (!lst)
		return (0);
	counted = 0;
	while (lst->next)
	{
		counted++;
		lst = lst->next;
	}
	return (counted + 1);
}
