/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:14:08 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/21 02:23:46 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	char			*cpsrc;

	cpsrc = (char*)src;
	if (!dest && !src)
		return (0);
	if (size == 0)
		return (ft_strlen(cpsrc));
	i = 0;
	while (i < size - 1 && cpsrc[i] != 0)
	{
		dest[i] = cpsrc[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen(cpsrc));
}
