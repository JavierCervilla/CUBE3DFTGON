/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:27:02 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/24 20:27:04 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*aux;

	if (!(aux = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	aux->content = content;
	aux->next = NULL;
	return (aux);
}
