/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:45:54 by doaltin           #+#    #+#             */
/*   Updated: 2024/01/18 20:55:54 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*x;

	new = 0;
	while (lst)
	{
		x = ft_lstnew(f(lst->content));
		if (!x)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, x);
		lst = lst->next;
	}
	return (new);
}
