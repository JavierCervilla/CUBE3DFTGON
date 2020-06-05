/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:20:47 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/19 19:53:15 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*aux;
	size_t	size;

	size = ft_strlen(s);
	if (!(aux = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	else
	{
		while (*s)
		{
			*aux = *s;
			aux++;
			s++;
		}
		*aux = 0;
		return (aux - size);
	}
}
