/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:54:39 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 16:26:15 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		ft_init_bmp_header(t_file *f, t_bmp *bmp)
{
	bmp->image_size = f->h * f->w;
	bmp->file_size = 54 + 4 * bmp->image_size;
	bmp->reserved1 = 0;
	bmp->reserved1 = 0;
	bmp->offset_bits = 14;
	bmp->size_header = 40;
	bmp->width = f->w;
	bmp->height = f->h;
	bmp->planes = 1;
	bmp->bit_count = 32;
	bmp->compression = 0;
	bmp->image_size = bmp->file_size;
	bmp->ppm_x = 100 * 39.375;
	bmp->ppm_y = 100 * 39.375;
	bmp->clr_used = 0;
	bmp->clr_important = 0;
}

void		ft_create_bmp(t_file *f)
{
	int		fd;
	int		i[3];
	int		cp[f->h * f->w - 1];
	t_bmp	bmp;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	ft_init_bmp_header(f, &bmp);
	fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	write(fd, "BM", 2);
	write(fd, &bmp, sizeof(bmp));
	while (++i[0] < f->h)
	{
		i[1] = 0;
		while (i[1] < f->w)
		{
			cp[i[2]] = *(f->ml.frame.data + (f->w * (f->h - 1 - i[0]) + i[1]));
			i[1]++;
			i[2]++;
		}
	}
	write(fd, &cp, f->h * f->w * 4);
	close(fd);
	ft_exit_game(f);
}
