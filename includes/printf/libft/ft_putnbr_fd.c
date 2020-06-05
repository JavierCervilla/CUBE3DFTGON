/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:39:36 by jcervill          #+#    #+#             */
/*   Updated: 2019/11/24 14:45:59 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int numero_puto;

	numero_puto = nb;
	if (numero_puto < 0)
	{
		ft_putchar_fd('-', fd);
		numero_puto = numero_puto * -1;
	}
	if (numero_puto >= 10)
	{
		ft_putnbr_fd(numero_puto / 10, fd);
		ft_putchar_fd((numero_puto % 10) + '0', fd);
	}
	else
	{
		ft_putchar_fd(numero_puto + '0', fd);
	}
}
