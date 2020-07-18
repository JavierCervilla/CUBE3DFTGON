/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:06:24 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 04:34:44 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int			ft_check_and_move(t_file *f)
{
	double dirxaux;
	double planexaux;

	if (f->mv.w == 1)
		ft_move_up(f);
	if (f->mv.s == 1)
		ft_move_dwn(f);
	if (f->mv.r == 1)
		ft_rot_r(f, dirxaux, planexaux);
	if (f->mv.l == 1)
		ft_rot_l(f, dirxaux, planexaux);
	if (f->mv.a == 1)
		ft_move_l(f);
	if (f->mv.d == 1)
		ft_move_r(f);
	return (0);
}

int			ft_key_press(int key, t_file *f)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		f->mv.w = 1;
	if (key == KEY_LEFT)
		f->mv.l = 1;
	if (key == KEY_S)
		f->mv.s = 1;
	if (key == KEY_RIGHT)
		f->mv.r = 1;
	if (key == KEY_D)
		f->mv.d = 1;
	if (key == KEY_A)
		f->mv.a = 1;
	return (0);
}

int			ft_key_release(int key, t_file *f)
{
	if (key == KEY_ESC)
		ft_exit_game(f);
	if (key == KEY_W)
		f->mv.w = 0;
	if (key == KEY_RIGHT)
		f->mv.r = 0;
	if (key == KEY_S)
		f->mv.s = 0;
	if (key == KEY_LEFT)
		f->mv.l = 0;
	if (key == KEY_D)
		f->mv.d = 0;
	if (key == KEY_A)
		f->mv.a = 0;
	return (0);
}

int			ft_move_and_draw(t_file *f)
{
	ft_check_and_move(f);
	mlx_destroy_image(f->ml.mlx, f->ml.frame.img);
	f->ml.frame.img = mlx_new_image(f->ml.mlx, f->w, f->h);
	f->ml.frame.data = (int*)mlx_get_data_addr(f->ml.frame.img,
		&f->ml.bitspp, &f->ml.size_line, &f->ml.end);
	ft_initraycast(f);
	ft_sprite(f);
	mlx_put_image_to_window(f->ml.mlx, f->ml.window, f->ml.frame.img, 0, 0);
}
