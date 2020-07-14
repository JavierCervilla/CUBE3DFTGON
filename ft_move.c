/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/14 01:35:40 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_canmove(int x)
{
	if (x == 1)
		return (0);
	else
		return (1);
}

static void	ft_move_up(t_file *f)
{
	if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.dir.x * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x += f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y + f->ml.dir.y * MOV)]))
		f->ml.pos.y += f->ml.dir.y * MOV;
}

static void	ft_move_dwn(t_file *f)
{
	if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.dir.x * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x -= f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y - f->ml.dir.y * MOV)]))
		f->ml.pos.y -= f->ml.dir.y * MOV;
}

static void	ft_rot_r(t_file *f, double dirxaux, double planexaux)
{
	dirxaux = f->ml.dir.x;
	planexaux = f->ml.plane.x;
	f->ml.dir.x = f->ml.dir.x * cos(-ROT) - f->ml.dir.y * sin(-ROT);
	f->ml.dir.y = dirxaux * sin(-ROT) + f->ml.dir.y * cos(-ROT);
	f->ml.plane.x = f->ml.plane.x * cos(-ROT) - f->ml.plane.y * sin(-ROT);
	f->ml.plane.y = planexaux * sin(-ROT) + f->ml.plane.y * cos(-ROT);
}

static void	ft_rot_l(t_file *f, double dirxaux, double planexaux)
{
	dirxaux = f->ml.dir.x;
	planexaux = f->ml.plane.x;
	f->ml.dir.x = f->ml.dir.x * cos(ROT) - f->ml.dir.y * sin(ROT);
	f->ml.dir.y = dirxaux * sin(ROT) + f->ml.dir.y * cos(ROT);
	f->ml.plane.x = f->ml.plane.x * cos(ROT) - f->ml.plane.y * sin(ROT);
	f->ml.plane.y = planexaux * sin(ROT) + f->ml.plane.y * cos(ROT);
}

static void	ft_move_l(t_file *f)
{
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y + f->ml.dir.x * MOV)]))
		f->ml.pos.y += f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.dir.y * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x -= f->ml.dir.y * MOV;
}

static void	ft_move_r(t_file *f)
{
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y - f->ml.dir.x * MOV)]))
		f->ml.pos.y -= f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.dir.y * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x += f->ml.dir.y * MOV;
}

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
		exit(0);
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
	if (f->mv.a || f->mv.s || f->mv.d || f->mv.w || f->mv.l || f->mv.r)
	{ 
		mlx_destroy_image(f->ml.mlx, f->ml.frame.img);
		f->ml.frame.img = mlx_new_image(f->ml.mlx, f->w, f->h);
		f->ml.frame.data = (int*)mlx_get_data_addr(f->ml.frame.img, &f->ml.bitspp, &f->ml.size_line, &f->ml.end);
		ft_initraycast(f);
		ft_sprite(f);
	}
	mlx_put_image_to_window(f->ml.mlx, f->ml.window, f->ml.frame.img, 0, 0);
}
