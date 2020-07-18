/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:52:14 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 19:01:22 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		ft_init_file_struct(t_file *f)
{
	int i;

	i = 0;
	f->w = 0;
	f->h = 0;
	f->rtn = 0;
	f->sprite = 0;
	while (i < 4)
		f->texture[i++] = 0;
	i = 0;
	while (i < 3)
		f->cc[i++] = -1;
	while (i >= 0)
		f->cf[i--] = -1;
	f->c_c = 0;
	f->c_f = 0;
	ft_init_file_struct2(f);
}

void		ft_init_file_struct2(t_file *f)
{
	f->mapreaded = -1;
	f->buff = ft_strdup("");
	f->nfil = 0;
	f->ncolmax = 0;
	f->dir = '\0';
	f->pos[0] = 0;
	f->pos[1] = 0;
	f->sprite = 0;
	f->sprite_num = 0;
	f->mv.a = 0;
	f->mv.d = 0;
	f->mv.l = 0;
	f->mv.r = 0;
	f->mv.s = 0;
	f->mv.w = 0;
}

void		ft_init_mlx_struct2(t_file *f)
{
	f->ml.step.x = 0;
	f->ml.step.y = 0;
	f->ml.camerax = 0;
	f->ml.map.x = 0;
	f->ml.map.y = 0;
	f->ml.lineheight = 0;
	f->ml.perpwalldist = 0;
	f->ml.drawstart = 0;
	f->ml.drawend = 0;
	f->ml.side = 0;
	f->ml.x = 0;
	f->ml.t_side = 0;
	f->ml.textx = 0;
	f->ml.texty = 0;
	f->ml.textstep = 0.0;
}

void		ft_init_mlx_struct(t_file *f)
{
	f->ml.pos.x = 0.0;
	f->ml.pos.y = 0.0;
	f->ml.dir.x = 0.0;
	f->ml.dir.y = 0.0;
	f->ml.plane.x = 0.0;
	f->ml.plane.y = 0.0;
	f->ml.side = 0;
	f->ml.ray.x = 0;
	f->ml.ray.y = 0;
	f->ml.deltadist.x = 0;
	f->ml.deltadist.y = 0;
	f->ml.raylength.x = 0;
	f->ml.raylength.y = 0;
	ft_init_mlx_struct2(f);
}
