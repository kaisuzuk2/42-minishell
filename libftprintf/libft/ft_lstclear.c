/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:04:12 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/04/28 13:52:40 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*next;

	if (lst == NULL)
		return ;
	p = *lst;
	while (p)
	{
		next = p->next;
		ft_lstdelone(p, (*del));
		p = next;
	}
	*lst = NULL;
}
