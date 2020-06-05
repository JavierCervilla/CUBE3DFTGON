/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:54:22 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/21 00:46:36 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int						sign;
	unsigned long long int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\n' || *str == '\f' || *str == '\r' ||
			*str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nbr = (nbr * 10) + *str - '0';
		str++;
	}
	return (sign * nbr);
}
