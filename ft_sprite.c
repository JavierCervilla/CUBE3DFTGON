/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:03:09 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/14 00:48:36 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_sp(t_file *f)
{
	int i;

	if (!(f->ml.sp = (t_sprite *)malloc((sizeof(t_sprite) * f->sprite_num))))
		ft_handle_error("SPRITE.malloc error");
	if (!(f->ml.sp_order = (int*)malloc((sizeof(int) * f->sprite_num))))
		ft_handle_error("SPRITE.malloc error");
		else
	{
		i = 0;
		while (i < f->sprite_num)
		{
			f->ml.sp_order[i] = i;
			i++;
		}
	}
}

void		ft_calc_pos(t_file *f)
{
	int i;
	int j;
	int	k;

	i = 0;
	k = 0;
	while (i < f->nColMax)
	{
		j = 0;
		while (j < f->nFil)
		{
			if (f->map[j][i] == 2)
			{
				f->ml.sp[k].pos.x = j + 0.6;
				f->ml.sp[k].pos.y = i + 0.6;
				k++;
			}
			j++;
		}
		i++;
	}
}

static void	ft_sort_sprites(t_file *f)
{
	int i;
	int j;
	int swap;
	
	i = 0;
	j = 0;
	swap = 0;
	while (i < f->sprite_num - 1)
	{
		j = 0;
		while (j < f->sprite_num - 1)
		{
			if (f->ml.sp[f->ml.sp_order[j]].distance < f->ml.sp[f->ml.sp_order[j + 1]].distance)
			{
				swap = f->ml.sp_order[j];
				f->ml.sp_order[j] = f->ml.sp_order[j + 1];
				f->ml.sp_order[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

static void	ft_calc_dist(t_file *f)
{
	int i;
	
	i = 0;
	while (i < f->sprite_num)
	{
		f->ml.sp[i].distance = ((f->ml.pos.x - f->ml.sp[i].pos.x) *
			(f->ml.pos.x - f->ml.sp[i].pos.x)) +
			((f->ml.pos.y - f->ml.sp[i].pos.y) *
			(f->ml.pos.y - f->ml.sp[i].pos.y));
		i++;
	}
}

void	debug(t_file *f)
{
	int i = 0;
	printf("------sprite------\n");
	while (i < f->sprite_num){
		printf("pos[%f][%f]\n", f->ml.sp[i].pos.x, f->ml.sp[i].pos.y);
		printf("campos[%f][%f]\n", f->ml.sp[i].cam_pos.x, f->ml.sp[i].cam_pos.y);
		printf("dist: %f\n", f->ml.sp[i].distance);
		
		i++;
	}
	i = 0;
	printf("-----sort----\n");
	while (i < f->sprite_num){
		printf("pos[%f][%f]\n", f->ml.sp[f->ml.sp_order[i]].pos.x, f->ml.sp[f->ml.sp_order[i]].pos.y);
		printf("dist: %f\n", f->ml.sp[f->ml.sp_order[i]].distance);
		i++;
	}
}

void ft_calc_rel_dist(t_file *f)
{
	int i;
	int stripe;
	int y;
	double d;
	int color;
	int seg;
	
	i = 0;
	while (i < f->sprite_num)
	{
		f->ml.sp[f->ml.sp_order[i]].cam_pos.x = f->ml.sp[f->ml.sp_order[i]].pos.x - f->ml.pos.x;
		f->ml.sp[f->ml.sp_order[i]].cam_pos.y = f->ml.sp[f->ml.sp_order[i]].pos.y - f->ml.pos.y;
		f->ml.inv_det = 1 / (f->ml.plane.x * f->ml.dir.y - f->ml.dir.x * f->ml.plane.y);
		f->ml.transform.x = f->ml.inv_det * (f->ml.dir.y * f->ml.sp[f->ml.sp_order[i]].cam_pos.x - f->ml.dir.x * f->ml.sp[f->ml.sp_order[i]].cam_pos.y);
		f->ml.transform.y = f->ml.inv_det * (- f->ml.plane.y * f->ml.sp[f->ml.sp_order[i]].cam_pos.x + f->ml.plane.x * f->ml.sp[f->ml.sp_order[i]].cam_pos.y);
		f->ml.sp_screen_x = (int)((f->w / 2) * (1 + f->ml.transform.x / f->ml.transform.y));
		f->ml.sp_height = abs((int)(f->h / f->ml.transform.y));
		f->ml.start_sp_y = - f->ml.sp_height / 2 + f->h / 2;
		if (f->ml.start_sp_y < 0)
			f->ml.start_sp_y = 0;
		f->ml.end_sp_y = f->ml.sp_height / 2 + f->h / 2;
		if (f->ml.end_sp_y >= f->h)
			f->ml.end_sp_y = f->h - 1;
		// calc width
		f->ml.sp_width = abs((int)(f->h / f->ml.transform.y));
		f->ml.start_sp_x = - f->ml.sp_width / 2 + f->ml.sp_screen_x;
		if (f->ml.start_sp_x < 0)
			f->ml.start_sp_x = 0;
		f->ml.end_sp_x = f->ml.sp_width / 2 + f->ml.sp_screen_x;
		if (f->ml.end_sp_x >= f->w)
			f->ml.end_sp_x = f->w - 1;
		// a dibujar
		stripe = f->ml.start_sp_x;
		while (stripe < f->ml.end_sp_x)
		{
			f->ml.tex_x = (int)(256 * (stripe - (- f->ml.sp_width / 2 + f->ml.sp_screen_x))
			* f->ml.text[4].width / f->ml.sp_width) / 256 &
			(f->ml.text[4].width - 1);
			if (f->ml.transform.y > 0 && stripe > 0 && stripe < f->w && f->ml.transform.y < f->ml.zbuff[stripe])
			{
				y = f->ml.start_sp_y;
				while (y < f->ml.end_sp_y)
				{
					d = (y) * 256 - f->h * 128 + f->ml.sp_height * 128;
					f->ml.tex_y = (int)((d * f->ml.text[4].height) / f->ml.sp_height) / 256 & (f->ml.text[4].height - 1);
					seg = f->ml.text[4].width * f->ml.tex_y + f->ml.tex_x;
					if (seg >= 0)
						color = f->ml.text[4].data[seg];
					if (color != f->ml.text[4].data[0])
						*(f->ml.frame.data + (y * f->w) + stripe) = color;
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	ft_sprite(t_file *f)
{
	ft_calc_pos(f);
	ft_calc_dist(f);
	ft_sort_sprites(f);
	ft_calc_rel_dist(f);
}