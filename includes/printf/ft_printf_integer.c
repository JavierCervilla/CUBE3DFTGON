/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:28:53 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:42:46 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_space_creator(t_params *p)
{
	char	*spaces;
	int		i;

	spaces = "\0";
	i = p->num_spaces;
	if (!(spaces = (char *)malloc(sizeof(char) * (i + 1))))
		return ;
	spaces[i] = '\0';
	p->spaces = spaces;
	while (i > 0)
	{
		if (p->zero == 1 && (p->precision < p->lenstr) && p->noprecision == 0)
			*spaces = '0';
		else if (p->noprecision == 1 && p->zero == 1 && p->num_0 == 0)
			*spaces = ' ';
		else
			*spaces = ' ';
		if (p->zero == 1 && p->num_0 == 1)
			*spaces = ' ';
		spaces++;
		i--;
	}
}

void	ft_zeros_creator(t_params *p)
{
	char	*zeros;
	int		i;

	zeros = "\0";
	i = p->num_zeros;
	if (!(zeros = (char *)malloc(sizeof(char) * (i + 1))))
		return ;
	zeros[i] = '\0';
	p->zeros = zeros;
	while (i > 0)
	{
		if (p->zero == 1 && p->precision > p->width && p->width > 0)
			*zeros = ' ';
		else
			*zeros = '0';
		zeros++;
		i--;
	}
}

void	ft_finalstr2print1(t_params *p)
{
	if (p->minus == 0 && p->zero == 0)
		p->final_str = ft_strjoin(p->final_str, p->spaces);
	if (p->isneg && p->zero == 0)
	{
		p->isneg = 0;
		p->final_str = ft_strjoin(p->final_str, "-");
	}
	if (p->zero == 1)
	{
		if (p->isneg == 1 && ((!p->zeros && !p->spaces) || p->spaces[0] == '0'))
		{
			p->final_str = ft_strjoin(p->final_str, "-");
		}
		p->final_str = ft_strjoin(p->final_str, p->spaces);
		if (p->isneg == 1 && ((p->zeros[0] == 0 && p->spaces[0] == 0)
					|| p->zeros[0] == '0' || p->spaces[0] == ' '))
		{
			p->final_str = ft_strjoin(p->final_str, "-");
		}
		p->final_str = ft_strjoin(p->final_str, p->zeros);
		p->final_str = ft_strjoin(p->final_str, p->str);
		ft_putstrfd(p->final_str, p);
	}
	ft_finalstr2print2(p);
}

void	ft_finalstr2print2(t_params *p)
{
	if (p->minus == 0 && p->type != 'g' && p->zero == 0)
	{
		p->final_str = ft_strjoin(p->final_str, p->zeros);
		p->final_str = ft_strjoin(p->final_str, p->str);
		ft_putstrfd(p->final_str, p);
	}
	if (p->minus == 1 && p->type != 'g' && p->zero == 0)
	{
		p->final_str = ft_strjoin(p->final_str, p->zeros);
		p->final_str = ft_strjoin(p->final_str, p->str);
		p->final_str = ft_strjoin(p->final_str, p->spaces);
		ft_putstrfd(p->final_str, p);
	}
	if (p->minus == 1 && p->type == 'g' && p->zero == 0)
		ft_putstrfd(p->spaces, p);
	if (p->minus == 0 && p->type == 'g' && p->zero == 0)
		ft_putstrfd(p->spaces, p);
}

void	ft_num2str(t_params *p)
{
	int		num;

	num = (int)va_arg(p->ap, int);
	p->str = ft_itoa(num);
	if (num == 0 && p->noprecision == 1 && p->precision >= 0)
	{
		p->num_0 = 1;
		p->str = ft_strdup("");
	}
	if (num == 0 && p->noprecision == 1 && p->precision < 0)
	{
		p->str = ft_strdup("0");
	}
	if (num < 0 && (p->precision != 0 || p->width != 0))
	{
		p->isneg = 1;
		p->width--;
		p->str++;
	}
	p->lenstr = ft_strlen_int(p->str);
	ft_check_width_precision1(p);
	ft_check_width_precision2(p);
	ft_zeros_creator(p);
	ft_space_creator(p);
	ft_finalstr2print1(p);
}
