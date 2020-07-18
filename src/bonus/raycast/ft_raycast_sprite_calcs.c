/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_sprite_calcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:17:00 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 04:35:03 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static void	ft_draw_sprites(t_file *f, int i, int stripe)
{
	double	d;
	int		y;
	int		seg;
	int		color;

	f->ml.tex_x = (int)(256 * (stripe - (-f->ml.sp_width / 2 +
		f->ml.sp_screen_x))
	* f->ml.text[4].width / f->ml.sp_width) / 256 &
	(f->ml.text[4].width - 1);
	if (f->ml.transform.y > 0 && stripe > 0 && stripe < f->w &&
		f->ml.transform.y < f->ml.zbuff[stripe])
	{
		y = f->ml.start_sp_y - 1;
		while (++y < f->ml.end_sp_y)
		{
			d = (y) * 256 - f->h * 128 + f->ml.sp_height * 128;
			f->ml.tex_y = (int)((d * f->ml.text[4].height) / f->ml.sp_height)
				/ 256 & (f->ml.text[4].height - 1);
			seg = f->ml.text[4].width * f->ml.tex_y + f->ml.tex_x;
			if (seg >= 0)
				color = f->ml.text[4].data[seg];
			if (color != f->ml.text[4].data[0])
				*(f->ml.frame.data + (y * f->w) + stripe) = color;
		}
	}
}

static void	ft_calc_width(t_file *f, int i)
{
	f->ml.sp_width = abs((int)(f->h / f->ml.transform.y));
	f->ml.start_sp_x = -f->ml.sp_width / 2 + f->ml.sp_screen_x;
	if (f->ml.start_sp_x < 0)
		f->ml.start_sp_x = 0;
	f->ml.end_sp_x = f->ml.sp_width / 2 + f->ml.sp_screen_x;
	if (f->ml.end_sp_x >= f->w)
		f->ml.end_sp_x = f->w - 1;
}

static void	ft_precalcs(t_file *f, int i)
{
	f->ml.sp[f->ml.sp_order[i]].cam_pos.x =
		f->ml.sp[f->ml.sp_order[i]].pos.x - f->ml.pos.x;
	f->ml.sp[f->ml.sp_order[i]].cam_pos.y =
		f->ml.sp[f->ml.sp_order[i]].pos.y - f->ml.pos.y;
	f->ml.inv_det = 1 / (f->ml.plane.x * f->ml.dir.y
		- f->ml.dir.x * f->ml.plane.y);
	f->ml.transform.x = f->ml.inv_det * (f->ml.dir.y *
		f->ml.sp[f->ml.sp_order[i]].cam_pos.x -
		f->ml.dir.x * f->ml.sp[f->ml.sp_order[i]].cam_pos.y);
	f->ml.transform.y = f->ml.inv_det * (-f->ml.plane.y *
		f->ml.sp[f->ml.sp_order[i]].cam_pos.x +
		f->ml.plane.x * f->ml.sp[f->ml.sp_order[i]].cam_pos.y);
	f->ml.sp_screen_x = (int)((f->w / 2) *
		(1 + f->ml.transform.x / f->ml.transform.y));
	f->ml.sp_height = abs((int)(f->h / f->ml.transform.y));
	f->ml.start_sp_y = -f->ml.sp_height / 2 + f->h / 2;
	if (f->ml.start_sp_y < 0)
		f->ml.start_sp_y = 0;
	f->ml.end_sp_y = f->ml.sp_height / 2 + f->h / 2;
	if (f->ml.end_sp_y >= f->h)
		f->ml.end_sp_y = f->h - 1;
}

void		ft_calc_rel_dist(t_file *f)
{
	int i;
	int stripe;

	i = 0;
	while (i < f->sprite_num)
	{
		ft_precalcs(f, i);
		ft_calc_width(f, i);
		stripe = f->ml.start_sp_x;
		while (stripe < f->ml.end_sp_x)
		{
			ft_draw_sprites(f, i, stripe);
			stripe++;
		}
		i++;
	}
}
