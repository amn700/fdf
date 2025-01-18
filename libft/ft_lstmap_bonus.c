/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:41:42 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 11:52:57 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		data = f(lst->content);
		node = ft_lstnew(data);
		if (!node)
		{
			del(data);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}
