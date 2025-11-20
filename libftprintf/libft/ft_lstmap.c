/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:13:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/04/28 14:33:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*content;

	res = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		if (content == NULL)
		{
			ft_lstclear(&res, (*del));
			return (NULL);
		}
		new = ft_lstnew(content);
		if (new == NULL)
		{
			free(content);
			ft_lstclear(&res, (*del));
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
