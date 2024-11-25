/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:35:14 by nozkara            #+#    #+#             */
/*   Updated: 2023/12/15 16:01:03 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(void *content)
{
	t_list *rtrn;

	rtrn = malloc(sizeof(t_list));
	if (!rtrn)
		return (0);
	rtrn->content = content;
	rtrn->next = 0;
	return (rtrn);
}
