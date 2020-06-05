/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:00:04 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/21 02:22:30 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*srccpy;
	char	*dstcpy;
	size_t	i;

	i = -1;
	dstcpy = (char *)dst;
	srccpy = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (srccpy > dstcpy)
	{
		while (++i < len)
			dstcpy[i] = srccpy[i];
	}
	else
	{
		while ((int)(--len) >= 0)
			dstcpy[len] = srccpy[len];
	}
	return (dst);
}
