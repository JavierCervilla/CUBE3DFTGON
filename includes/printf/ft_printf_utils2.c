/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:08:21 by jcervill          #+#    #+#             */
/*   Updated: 2020/01/22 09:09:38 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchrmod(const char *s, int c)
{
	while (*s && *s != (char)c && *s != '%')
		s++;
	if (*s == (char)c)
		return ((char *)s);
	if (!c && (*s == '\0' || *s == '%'))
		return ((char *)s);
	return (NULL);
}

int		ft_strlen_int(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putcharfd(char c, t_params *p)
{
	write(FD, &c, 1);
	p->len++;
}

void	ft_putchar(char c, t_params *p)
{
	char str[2];

	str[0] = c;
	str[1] = '\0';
	ft_strjoin(p->final_str, str);
	ft_putcharfd(c, p);
}
