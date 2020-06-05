/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:44:36 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:46:08 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# ifndef FD
#  define FD 1
# endif

typedef struct	s_params
{
	char		*format;
	char		*final_str;
	char		*str;
	char		*spaces;
	char		*zeros;
	char		type;
	va_list		ap;
	int			num_spaces;
	int			len;
	int			zero;
	int			minus;
	int			width;
	int			precision;
	int			lenstr;
	int			isneg;
	int			noprecision;
	int			point;
	int			noprint;
	int			num_zeros;
	int			num_0;
}				t_params;

int				ft_printf(const char *format, ...);
void			ft_clean(t_params *p);
void			ft_check_precission(t_params *p);
void			ft_check_width(t_params *p);
void			ft_check_flags(t_params *p);
int				ft_typers(char c);
void			ft_check(t_params *p);
void			ft_char2str(t_params *p);
void			ft_str2str(t_params *p);
void			ft_unsignum2str(t_params *p);
char			*ft_itoaunsigned(unsigned int n);
void			ft_num2str(t_params *p);
void			ft_int2hex(t_params *p);
void			ft_arg2hex(t_params *p);
void			ft_putnbrfd(unsigned long int nb, t_params *p, char c);
void			ft_check_width_precision1(t_params *p);
void			ft_check_width_precision2(t_params *p);
void			ft_space_creator(t_params *p);
void			ft_zeros_creator(t_params *p);
void			ft_putstrfd(char *s, t_params *p);
void			ft_putchar_tostr(char c, t_params *p);
void			ft_putchar(char c, t_params *p);
void			ft_putcharfd(char c, t_params *p);
int				ft_strlen_int(const char *str);
char			*ft_strchrmod(const char *s, int c);
void			ft_finalstr2print1(t_params *p);
void			ft_finalstr2print2(t_params *p);
#endif
