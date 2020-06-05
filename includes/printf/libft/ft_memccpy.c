/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:55:33 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/19 13:55:46 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cpdest;
	unsigned char	*cpsrc;
	size_t			i;

	cpdest = (unsigned char *)dest;
	cpsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cpdest[i] = cpsrc[i];
		if (cpdest[i] == (unsigned char)c || cpsrc[i] == (unsigned char)c)
			return (dest + (i + 1));
		i++;
	}
	return (NULL);
}
