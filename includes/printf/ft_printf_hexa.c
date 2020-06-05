/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:28:22 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:34:56 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_arg2hex(t_params *p)
{
	unsigned long int hex;

	hex = (unsigned long int)va_arg(p->ap, unsigned long int);
	ft_putnbrfd(hex, p, 'W');
	if (hex == 0 && p->point == 1)
		p->str = ft_strdup("");
	if (p->point == 0 || p->width > p->precision)
		p->str = ft_strjoin("0x", p->str);
	else if (p->point == 1)
		p->final_str = ft_strjoin("0x", p->final_str);
	p->lenstr = ft_strlen_int(p->str);
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_zeros_creator(p);
	ft_space_creator(p);
	ft_finalstr2print1(p);
}

void	ft_int2hex(t_params *p)
{
	unsigned int hex;

	hex = (unsigned int)va_arg(p->ap, unsigned int);
	if (p->type == 'x')
		ft_putnbrfd(hex, p, 'W');
	else if (p->type == 'X')
		ft_putnbrfd(hex, p, '7');
	if (hex == 0 && p->noprecision == 1 && p->precision >= 0)
		p->str = ft_strdup("");
	if (hex == 0 && p->noprecision == 1 && p->precision < 0)
	{
		p->str = ft_strdup("0");
	}
	p->lenstr = ft_strlen_int(p->str);
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_zeros_creator(p);
	ft_space_creator(p);
	ft_finalstr2print1(p);
}

void	ft_unsignum2str(t_params *p)
{
	unsigned int num;

	num = (unsigned int)va_arg(p->ap, unsigned int);
	if (num == 0 && p->noprecision == 1 && p->precision >= 0)
	{
		p->num_0 = 1;
		p->str = ft_strdup("");
	}
	else
		p->str = ft_itoaunsigned(num);
	p->lenstr = ft_strlen_int(p->str);
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_zeros_creator(p);
	ft_space_creator(p);
	ft_finalstr2print1(p);
}
