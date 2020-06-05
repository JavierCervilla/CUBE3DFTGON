/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:01:15 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/25 16:57:23 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *element;

	if (alst != NULL)
	{
		element = *alst;
		if (*alst == NULL)
			*alst = new;
		else
		{
			while (element->next)
				element = element->next;
			element->next = new;
		}
	}
}
