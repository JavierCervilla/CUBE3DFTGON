/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:28:21 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 17:43:37 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static void	ft_set_res(char **res, int j, t_file *f)
{
	if (j == 1)
	{
		f->w = ft_atoi(res[j]);
		if (f->w > 1920)
			f->w = 1920;
		if (f->w < 200)
			f->w = 200;
	}
	if (j == 2)
	{
		f->h = ft_atoi(res[j]);
		if (f->h > 1080)
			f->h = 1080;
		if (f->h < 200)
			f->h = 200;
	}
}

int			ft_handle_resolution(t_file *f)
{
	char	**res;
	int		i;
	int		j;

	if (*f->line == 'R' && *f->line)
	{
		j = 1;
		res = ft_split(f->line, ' ');
		if (res[3] != 0)
			return (f->rtn = -1);
		while (j <= 2)
		{
			i = 0;
			while (res[j][i])
			{
				if (!ft_isdigit(res[j][i]))
					return (f->rtn = -1);
				i++;
			}
			ft_set_res(res, j, f);
			j++;
		}
		ft_free((void*)res);
	}
	return (f->rtn);
}
