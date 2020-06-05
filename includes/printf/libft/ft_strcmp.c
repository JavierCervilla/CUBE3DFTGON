/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez <dgomez@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:29:27 by dgomez            #+#    #+#             */
/*   Updated: 2020/03/07 15:08:16 by dgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
	{
		return (0);
	}
	while (*str1 && *str2)
	{
		if (*str1++ == *str2++)
		{
			i++;
		}
		else
			return (0);
	}
	return (i);
}
