/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:13:18 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/19 01:13:31 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str2;

	str2 = NULL;
	while (*s)
	{
		if (*s == (char)c)
			str2 = (char *)s;
		s++;
	}
	if (*s == (char)c)
		str2 = (char *)s;
	return (str2);
}
