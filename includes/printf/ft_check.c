/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:15:19 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:15:50 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_flags(t_params *p)
{
	if (*p->format == '0')
	{
		p->zero = 1;
		p->format++;
	}
	if (*p->format == '-')
	{
		p->zero = 0;
		p->minus = 1;
		p->format++;
	}
}

void	ft_check_width(t_params *p)
{
	if (ft_isdigit(*p->format))
		p->width = ft_atoi(p->format);
	if (*p->format == '*')
	{
		p->width = va_arg(p->ap, int);
		if (p->width < 0)
		{
			p->zero = 0;
			p->minus = 1;
			p->width = p->width * -1;
		}
		p->format++;
	}
}

void	ft_check_precission(t_params *p)
{
	char *aux;

	if ((aux = ft_strchrmod(p->format, '.')))
	{
		p->point = 1;
		aux++;
		if (*aux == '*')
		{
			p->precision = va_arg(p->ap, int);
			if (p->precision == 0)
				p->noprecision = 1;
		}
		else if (ft_isdigit(*aux))
		{
			p->precision = ft_atoi(aux);
			if (p->precision == 0)
				p->noprecision = 1;
		}
		else if (ft_typers(*aux) == 1)
			p->noprecision = 1;
		p->format++;
	}
	else
		p->point = 0;
}

void	ft_check_width_precision1(t_params *p)
{
	if (p->type != 's')
	{
		if (p->precision > 0 && p->precision < p->lenstr)
			p->precision = p->lenstr;
		if (p->width > 0 && p->width < p->precision)
			p->width = p->precision;
		if (p->precision >= p->lenstr && p->precision > 0)
			p->num_zeros = p->precision - p->lenstr;
		else if (p->precision > 0 && p->precision < p->lenstr)
			p->num_zeros = 0;
		else
			p->num_zeros = 0;
		p->num_spaces = p->width - (p->num_zeros + p->lenstr);
	}
}

void	ft_check_width_precision2(t_params *p)
{
	if (p->type == 's')
	{
		if (p->precision > p->lenstr || p->precision < 0)
		{
			p->noprecision = 0;
			p->precision = p->lenstr;
		}
		if (p->width < p->precision && p->precision > 0)
			p->width = p->precision;
		else
			p->num_spaces = p->width - p->precision;
		if (p->point && p->noprecision)
			p->noprint = 1;
		if (p->width < p->lenstr)
			p->num_spaces = 0;
		else
			p->num_spaces = p->width - p->lenstr;
	}
}
