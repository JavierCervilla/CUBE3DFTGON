/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:37:09 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/25 17:07:41 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *aux;
	t_list *start;
	t_list *new;

	if (lst)
	{
		aux = lst;
		if (!(start = ft_lstnew(f(lst->content))))
			return (NULL);
		aux = aux->next;
		while (aux)
		{
			if (!(new = ft_lstnew(f(aux->content))))
			{
				ft_lstclear(&start, del);
				return (NULL);
			}
			ft_lstadd_back(&start, new);
			aux = aux->next;
		}
		return (start);
	}
	return (NULL);
}
