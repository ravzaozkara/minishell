/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:35:35 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/10 18:44:10 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!new)
		return;
	if (!lst || !*lst)
	{
		*lst = new;
		return;
	}
	temp = *lst;
	temp = ft_lstlast(temp);
	temp->next = new;
}
