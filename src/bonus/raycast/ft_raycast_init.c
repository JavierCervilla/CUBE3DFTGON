/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:57:44 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 19:01:22 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void			ft_fixing_def(t_file *f)
{
	if (f->ml.side == 0)
		f->ml.perpwalldist = (f->ml.map.x - f->ml.pos.x + (1 - f->ml.step.x)
			/ 2) / f->ml.ray.x;
	else
		f->ml.perpwalldist = (f->ml.map.y - f->ml.pos.y + (1 - f->ml.step.y)
			/ 2) / f->ml.ray.y;
	f->ml.lineheight = (int)(f->h / f->ml.perpwalldist) * 2;
	f->ml.drawstart = (-f->ml.lineheight / 2) + f->h / 2;
	if (f->ml.drawstart < 0)
		f->ml.drawstart = 0;
	f->ml.drawend = (f->ml.lineheight / 2) + f->h / 2;
	if (f->ml.drawend > f->h || f->ml.drawend == 0)
		f->ml.drawend = f->h - 1;
}

void			ft_calc_side(t_file *f)
{
	if (f->ml.raylength.x < f->ml.raylength.y)
	{
		f->ml.raylength.x += f->ml.deltadist.x;
		f->ml.map.x += f->ml.step.x;
		f->ml.side = 0;
	}
	else
	{
		f->ml.raylength.y += f->ml.deltadist.y;
		f->ml.map.y += f->ml.step.y;
		f->ml.side = 1;
	}
}

void			ft_recalc(t_file *f)
{
	f->ml.step.x = 0;
	f->ml.step.y = 0;
	f->ml.raylength.x = 0;
	f->ml.raylength.y = 0;
}

void			ft_calc_step(t_file *f)
{
	ft_recalc(f);
	if (f->ml.ray.x < 0)
	{
		f->ml.step.x = -1;
		f->ml.raylength.x = (f->ml.pos.x - f->ml.map.x) * f->ml.deltadist.x;
	}
	else
	{
		f->ml.step.x = 1;
		f->ml.raylength.x = (f->ml.map.x + 1.0 - f->ml.pos.x)
		* f->ml.deltadist.x;
	}
	if (f->ml.ray.y < 0)
	{
		f->ml.step.y = -1;
		f->ml.raylength.y = (f->ml.pos.y - f->ml.map.y) * f->ml.deltadist.y;
	}
	else
	{
		f->ml.step.y = 1;
		f->ml.raylength.y = (f->ml.map.y + 1.0 - f->ml.pos.y)
		* f->ml.deltadist.y;
	}
}

void			ft_init_rc(t_file *f)
{
	f->ml.map.x = (int)f->ml.pos.x;
	f->ml.map.y = (int)f->ml.pos.y;
	f->ml.camerax = (2 * f->ml.x / (double)f->w) - 1;
	f->ml.ray.x = f->ml.dir.x + f->ml.plane.x * f->ml.camerax;
	f->ml.ray.y = f->ml.dir.y + f->ml.plane.y * f->ml.camerax;
	f->ml.deltadist.x = fabs(1 / f->ml.ray.x);
	f->ml.deltadist.y = fabs(1 / f->ml.ray.y);
}
