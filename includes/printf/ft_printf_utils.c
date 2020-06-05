/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:05:02 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:04 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoaunsigned(unsigned int n)
{
	int				digits;
	unsigned int	num;
	char			*str;

	num = n;
	digits = 2;
	while (num /= 10)
		digits++;
	if (!(str = (char *)malloc(sizeof(char) * digits)))
		return (NULL);
	str[--digits] = 0;
	while (digits--)
	{
		str[digits] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

void	ft_putnbrfd(unsigned long int nb, t_params *p, char c)
{
	unsigned long int numero_puto;

	numero_puto = nb;
	if (numero_puto >= 16)
		ft_putnbrfd(numero_puto / 16, p, c);
	if ((numero_puto % 16) <= 9)
		ft_putchar_tostr((numero_puto % 16) + '0', p);
	if ((numero_puto % 16) >= 10)
		ft_putchar_tostr((numero_puto % 16) + c, p);
}

void	ft_putchar_tostr(char c, t_params *p)
{
	char str[2];

	str[0] = c;
	str[1] = '\0';
	p->str = ft_strjoin(p->str, str);
}

void	ft_putstrfd(char *s, t_params *p)
{
	int i;

	if (p->type == 'g' && p->minus == 1)
		ft_putcharfd('\0', p);
	if (s && FD)
	{
		i = 0;
		while (s[i])
		{
			ft_putchar(s[i], p);
			i++;
		}
	}
	if (p->type == 'g' && p->minus != 1)
		ft_putcharfd('\0', p);
}
