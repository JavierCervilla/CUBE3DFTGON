/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_init_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:01:02 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 04:34:59 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static void		ft_cast_init_dir2(t_file *f)
{
	if (f->dir == 'W')
	{
		f->ml.dir.x = 0.0;
		f->ml.dir.y = -1.0;
		f->ml.plane.x = -0.66;
		f->ml.plane.y = 0;
	}
	else if (f->dir == 'E')
	{
		f->ml.dir.x = 0.0;
		f->ml.dir.y = 1.0;
		f->ml.plane.x = 0.66;
		f->ml.plane.y = 0.0;
	}
	if (!(f->ml.zbuff = (double*)malloc(sizeof(double) * f->w)))
		ft_handle_error("MALLOC ERR. zbuff");
}

void			ft_cast_init_dir(t_file *f)
{
	if (f->dir == 'N')
	{
		f->ml.dir.x = -1.0;
		f->ml.dir.y = 0.0;
		f->ml.plane.x = 0;
		f->ml.plane.y = 0.66;
	}
	else if (f->dir == 'S')
	{
		f->ml.dir.x = 1.0;
		f->ml.dir.y = 0.0;
		f->ml.plane.x = 0.0;
		f->ml.plane.y = -0.66;
	}
	ft_cast_init_dir2(f);
}
