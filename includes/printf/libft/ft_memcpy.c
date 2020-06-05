/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:57:32 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/19 13:57:45 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*auxdest;
	const char	*auxsrc;

	auxdest = (char *)dest;
	auxsrc = (const char *)src;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*auxdest++ = *auxsrc++;
	}
	return (dest);
}
