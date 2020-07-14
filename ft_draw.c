/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/14 01:44:23 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void		ft_cast_init_dir(t_file *f)
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

void		ft_recalc(t_file *f)
{
	f->ml.step.x = 0;
	f->ml.step.y = 0;
	f->ml.raylength.x = 0;
	f->ml.raylength.y = 0;
}

void		ft_calc_step(t_file *f)
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

void		ft_calc_side(t_file *f)
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
	f->ml.textPos = (f->ml.drawStart - f->h / 2 + f->ml.lineheight / 2)
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
	while (i < f->ml.drawStart)
	{
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = 7719150;
		i++;
	}
	while (i <= f->ml.drawEnd)
	{
		f->ml.texty = (int)f->ml.textPos &
			(f->ml.text[f->ml.t_side].height - 1);
		f->ml.textPos += f->ml.textstep;
		color = f->ml.text[f->ml.t_side].data[f->ml.text[f->ml.t_side].height
			* f->ml.texty + f->ml.textx];
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = color;
		i++;
	}
	while (i <= f->h)
	{
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = 7364912;
		i++;
	}
}

static void		ft_init(t_file *f)
{
	// posicion en la matriz
	f->ml.map.x = (int)f->ml.pos.x;
	f->ml.map.y = (int)f->ml.pos.y;
	// plano de camera
	f->ml.camerax = (2 * f->ml.x / (double)f->w) - 1;
	f->ml.ray.x = f->ml.dir.x + f->ml.plane.x * f->ml.camerax;
	f->ml.ray.y = f->ml.dir.y + f->ml.plane.y * f->ml.camerax;
	f->ml.deltadist.x = (f->ml.ray.y == 0) ? 0 : ((f->ml.ray.x == 0) ? 1 : fabs(1 / f->ml.ray.x));
	f->ml.deltadist.y = (f->ml.ray.x == 0) ? 0 : ((f->ml.ray.y == 0) ? 1 : fabs(1 / f->ml.ray.y));
}

static void ft_fixing_def(t_file *f)
{
	if (f->ml.side == 0)
		f->ml.perpwalldist = (f->ml.map.x - f->ml.pos.x + (1 - f->ml.step.x) / 2) / f->ml.ray.x;
	else
		f->ml.perpwalldist = (f->ml.map.y - f->ml.pos.y + (1 - f->ml.step.y) / 2) / f->ml.ray.y;
	f->ml.lineheight = (int)(f->h / f->ml.perpwalldist) * 2;
	// calcular el pixel mas bajo y alto a pintar
	f->ml.drawStart = (-f->ml.lineheight / 2) + f->h / 2;
	if (f->ml.drawStart < 0)
		f->ml.drawStart = 0;
	f->ml.drawEnd = (f->ml.lineheight / 2) + f->h / 2;
	if (f->ml.drawEnd > f->h || f->ml.drawEnd == 0)
		f->ml.drawEnd = f->h - 1;
}

int			ft_initraycast(t_file *f)
{
	int hit; // detecta la colision con el muro

	f->ml.x = 0;
	while (f->ml.x < f->w) // raycast
	{
		// colision
		hit = 0;
		ft_init(f);
		// calc step
		ft_calc_step(f);
		// perform DDA
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