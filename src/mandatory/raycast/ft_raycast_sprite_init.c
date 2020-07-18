/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_sprite_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:15:18 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 19:00:49 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void		ft_init_sp(t_file *f)
{
	int		i;

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
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < f->ncolmax)
	{
		j = 0;
		while (j < f->nfil)
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

void		ft_sort_sprites(t_file *f)
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
			if (f->ml.sp[f->ml.sp_order[j]].distance <
				f->ml.sp[f->ml.sp_order[j + 1]].distance)
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

void		ft_calc_dist(t_file *f)
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

void		ft_sprite(t_file *f)
{
	ft_calc_pos(f);
	ft_calc_dist(f);
	ft_sort_sprites(f);
	ft_calc_rel_dist(f);
}
