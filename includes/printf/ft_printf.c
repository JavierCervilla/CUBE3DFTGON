/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:16:26 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:16:28 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_typers(char c)
{
	return (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u' ||
			c == 'p' || c == 'x' || c == 'X' || c == '%');
}

void	ft_check(t_params *p)
{
	if (p->type == 'c')
		ft_char2str(p);
	if (p->type == 's')
		ft_str2str(p);
	if (p->type == 'd' || p->type == 'i')
		ft_num2str(p);
	if (p->type == 'u')
		ft_unsignum2str(p);
	if (p->type == 'p')
		ft_arg2hex(p);
	if (p->type == 'x' || p->type == 'X')
		ft_int2hex(p);
	if (p->type == '%')
		ft_char2str(p);
}

void	ft_clean(t_params *p)
{
	p->final_str = "\0";
	p->str = "\0";
	p->type = '\0';
	p->zeros = "\0";
	p->spaces = "\0";
	p->minus = 0;
	p->zero = 0;
	p->precision = 0;
	p->width = 0;
	p->lenstr = 0;
	p->num_spaces = 0;
	p->num_zeros = 0;
	p->isneg = 0;
	p->lenstr = 0;
	p->noprecision = 0;
	p->point = 0;
	p->noprint = 0;
	p->num_0 = 0;
}

void	ft_fillstruct(t_params *p)
{
	while (*p->format != '\0')
	{
		ft_clean(p);
		if (*p->format == '%')
		{
			p->format++;
			ft_check_flags(p);
			if ((ft_typers(*p->format)) == 0)
			{
				ft_check_width(p);
				ft_check_precission(p);
			}
			while (ft_typers(*p->format) == 0)
				p->format++;
			p->type = *p->format++;
			ft_check(p);
		}
		else
		{
			ft_putcharfd(*p->format, p);
			p->format++;
		}
	}
}

int		ft_printf(const char *format, ...)
{
	t_params p;

	va_start(p.ap, format);
	p.format = (char *)format;
	p.len = 0;
	ft_clean(&p);
	ft_fillstruct(&p);
	va_end(p.ap);
	return (p.len);
}
