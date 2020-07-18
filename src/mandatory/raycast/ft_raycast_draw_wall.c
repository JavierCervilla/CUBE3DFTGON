/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_draw_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:03:45 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 19:02:01 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void		ft_texture_config(t_file *f)
{
	if (f->ml.side == 0)
		f->ml.wallx = f->ml.pos.y + f->ml.perpwalldist * f->ml.ray.y;
	else
		f->ml.wallx = f->ml.pos.x + f->ml.perpwalldist * f->ml.ray.x;
	f->ml.wallx -= floor(f->ml.wallx);
	f->ml.textx = (int)(f->ml.wallx * (double)f->ml.text[f->ml.t_side].width);
	if (f->ml.side == 0 && f->ml.ray.x > 0)
		f->ml.textx = f->ml.text[f->ml.t_side].width - f->ml.textx - 1;
	if (f->ml.side == 1 && f->ml.ray.y < 0)
		f->ml.textx = f->ml.text[f->ml.t_side].width - f->ml.textx - 1;
	f->ml.textstep = 1.0 * f->ml.text[f->ml.t_side].height / f->ml.lineheight;
	f->ml.textpos = (f->ml.drawstart - f->h / 2 + f->ml.lineheight / 2)
	* f->ml.textstep;
}

int			ft_set_wall(t_file *f)
{
	double	dx;
	double	dy;

	dx = f->ml.map.x - f->ml.pos.x;
	dy = f->ml.map.y - f->ml.pos.y;
	if (dx < 0 && f->ml.side == 0)
		f->ml.t_side = 3;
	else if (dx > 0 && f->ml.side == 0)
		f->ml.t_side = 2;
	else if (dy < 0 && f->ml.side == 1)
		f->ml.t_side = 1;
	else if (dy > 0 && f->ml.side == 1)
		f->ml.t_side = 0;
}

void		ft_color(t_file *f)
{
	if (f->map[(int)f->ml.map.x][(int)f->ml.map.y] == 1)
	{
		ft_set_wall(f);
	}
	if (f->map[(int)f->ml.map.x][(int)f->ml.map.y] == 2)
	{
		f->ml.color = 708;
	}
}

void		ft_draw_line(t_file *f)
{
	int i;
	int color;

	i = 0;
	while (i < f->ml.drawstart)
	{
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = f->c_c;
		i++;
	}
	while (i <= f->ml.drawend)
	{
		f->ml.texty = (int)f->ml.textpos &
			(f->ml.text[f->ml.t_side].height - 1);
		f->ml.textpos += f->ml.textstep;
		color = f->ml.text[f->ml.t_side].data[f->ml.text[f->ml.t_side].height
			* f->ml.texty + f->ml.textx];
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = color;
		i++;
	}
	while (i <= f->h)
	{
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = f->c_f;
		i++;
	}
}

int			ft_initraycast(t_file *f)
{
	int hit;

	f->ml.x = 0;
	while (f->ml.x < f->w)
	{
		hit = 0;
		ft_init_rc(f);
		ft_calc_step(f);
		while (hit == 0)
		{
			ft_calc_side(f);
			if (f->map[(int)f->ml.map.x][(int)f->ml.map.y] == 1)
				hit = 1;
		}
		ft_fixing_def(f);
		ft_set_wall(f);
		ft_texture_config(f);
		ft_draw_line(f);
		f->ml.zbuff[f->ml.x] = f->ml.perpwalldist;
		f->ml.x++;
	}
}
