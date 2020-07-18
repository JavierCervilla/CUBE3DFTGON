/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:30:57 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 18:44:34 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static int	localisdigit(t_file *f, char **test)
{
	int		i;
	int		j;

	i = 0;
	while (i <= 2)
	{
		j = 0;
		while (test[i][j])
		{
			if ((!ft_isdigit(test[i][j]) && test[i][j] != ' '))
				if (j > 0 && (test[i][j] == ' ' && ft_isdigit(test[i][j - 1])))
					return (f->rtn = -1);
			j++;
		}
		i++;
	}
	return (f->rtn);
}

int			ft_handle_cfloor(t_file *f)
{
	char	**test2;
	int		i;

	i = 0;
	if (*f->line == 'F' && *f->line)
	{
		test2 = ft_split(++f->line, ',');
		while (test2[i] != NULL)
			i++;
		i == 3 ? i = -1 : ft_handle_error_ptr("ERROR:CF, 2 it", (void*)test2);
		if (localisdigit(f, test2) == -1)
			ft_handle_error_ptr("ERROR: C_FLOOR", (void*)test2);
		if ((f->cf[0] = ft_atoi(test2[0])) >= 0)
			if (f->cf[0] > 255 || f->cf[0] < 0)
				f->rtn = -1;
		if ((f->cf[1] = ft_atoi(test2[1])) >= 0)
			if (f->cf[1] > 255 || f->cf[1] < 0)
				f->rtn = -1;
		if ((f->cf[2] = ft_atoi(test2[2])) >= 0)
			if (f->cf[2] > 255 || f->cf[2] < 0)
				f->rtn = -1;
		ft_free((void*)test2);
	}
	return (f->rtn);
}

int			ft_handle_croof(t_file *f)
{
	char	**test2;
	int		i;

	i = 0;
	if (*f->line == 'C' && *f->line)
	{
		test2 = ft_split(++f->line, ',');
		while (test2[i] != NULL)
			i++;
		i == 3 ? i = -1 : ft_handle_error_ptr("ERROR: CF, 2 it", (void*)test2);
		if (localisdigit(f, test2) == -1)
			ft_handle_error("ERROR: COLOR ROOF");
		if ((f->cc[0] = ft_atoi(test2[0])) >= 0)
			if (f->cc[0] > 255 || f->cc[0] < 0)
				return ((f->rtn = -1));
		if ((f->cc[1] = ft_atoi(test2[1])) >= 0)
			if (f->cc[1] > 255 || f->cc[1] < 0)
				return ((f->rtn = -1));
		if ((f->cc[2] = ft_atoi(test2[2])) >= 0)
			if (f->cc[2] > 255 || f->cc[2] < 0)
				return ((f->rtn = -1));
		ft_free((void*)test2);
	}
	return (f->rtn);
}

int			ft_handle_rgb(t_file *f)
{
	f->c_c = (int)(f->cc[0] * 256 * 256 + f->cc[1] * 256 + f->cc[2]);
	f->c_f = (int)(f->cf[0] * 256 * 256 + f->cf[1] * 256 + f->cf[2]);
}
