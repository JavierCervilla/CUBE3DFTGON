/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:27:52 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:37:44 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_str2str(t_params *p)
{
	p->str = (char *)va_arg(p->ap, char *);
	if (p->str == NULL)
		p->str = ft_strdup("(null)");
	if (p->precision > 0)
		p->str = ft_substr(p->str, 0, p->precision);
	if (p->noprecision == 1 || (p->point == 1 && p->precision == 0))
		p->str = ft_strdup("");
	p->lenstr = ft_strlen_int(p->str);
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_space_creator(p);
	if (p->minus == 0 && p->spaces)
		p->final_str = ft_strjoin(p->final_str, p->spaces);
	p->final_str = ft_strjoin(p->final_str, p->str);
	if (p->minus == 1 && p->spaces)
		p->final_str = ft_strjoin(p->final_str, p->spaces);
	ft_putstrfd(p->final_str, p);
}

void	ft_char2str(t_params *p)
{
	char str[2];

	if (p->type == 'c')
		str[0] = (char)va_arg(p->ap, int);
	else if (p->type == '%')
		str[0] = '%';
	str[1] = '\0';
	p->str = str;
	p->lenstr = ft_strlen_int(p->str);
	if (p->str[0] == '\0')
	{
		p->width--;
		p->type = 'g';
	}
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_zeros_creator(p);
	ft_space_creator(p);
	ft_finalstr2print1(p);
}
