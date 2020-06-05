/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec2hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 23:55:55 by jcervill          #+#    #+#             */
/*   Updated: 2020/03/31 17:47:32 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dec2hex(unsigned int n)
{
	unsigned int		aux;
	int					len;
	char				*str;

	aux = n;
	len = 1;
	while (aux /= 16)
		len++;
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if ((n % 16) < 10)
			str[len] = n % 16 + '0';
		if ((n % 16) > 9)
			str[len] = n % 16 + 'W';
		n = n / 16;
	}
	return (str);
}
