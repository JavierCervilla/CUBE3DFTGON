/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#             */
/*   Updated: 2020/03/30 12:41:29 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_canmove(int x)
{
	if (x == 1 || x == 2)
		return(0);
	else
		return(1);
}

int ft_check_and_move(t_file *f)
{
	double dirxAux;
	double planexAux;

	// arriba
	if (f->mv.w == 1)
	{
		if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.currentDir.x * MOV)][(int)f->ml.pos.y]))
			f->ml.pos.x += f->ml.currentDir.x * MOV;
		if (ft_canmove(f->map[(int)f->ml.pos.x][(int)(f->ml.pos.y + f->ml.currentDir.y * MOV)]))
			f->ml.pos.y += f->ml.currentDir.y * MOV;
	}
	// abajo
	if (f->mv.s == 1)
	{
		if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.currentDir.x *MOV)][(int)f->ml.pos.y]))
			f->ml.pos.x -= f->ml.currentDir.x * MOV;
		if (ft_canmove(f->map[(int)f->ml.pos.x][(int)(f->ml.pos.y - f->ml.currentDir.y * MOV)]))
			f->ml.pos.y -= f->ml.currentDir.y * MOV;
	}
	// dcha rot
	if (f->mv.r == 1)
	{
		dirxAux = f->ml.currentDir.x;
		planexAux = f->ml.plane.x;
		f->ml.currentDir.x = f->ml.currentDir.x * cos(-ROT) - f->ml.currentDir.y * sin(-ROT);
		f->ml.currentDir.y = dirxAux * sin(-ROT) + f->ml.currentDir.y * cos(-ROT);
		f->ml.plane.x = f->ml.plane.x * cos(-ROT) - f->ml.plane.y * sin(-ROT);
		f->ml.plane.y = planexAux * sin(-ROT) + f->ml.plane.y * cos(-ROT);
	}
	// izda rot
	if (f->mv.l == 1)
	{
		dirxAux = f->ml.currentDir.x;
		planexAux = f->ml.plane.x;
		f->ml.currentDir.x = f->ml.currentDir.x * cos(ROT) - f->ml.currentDir.y * sin(ROT);
		f->ml.currentDir.y = dirxAux * sin(ROT) + f->ml.currentDir.y * cos(ROT);
		f->ml.plane.x = f->ml.plane.x * cos(ROT) - f->ml.plane.y * sin(ROT);
		f->ml.plane.y = planexAux * sin(ROT) + f->ml.plane.y * cos(ROT);
	}
	// izda mov
	if(f->mv.a == 1)
	{
		if (ft_canmove(f->map[(int)f->ml.pos.x][(int)(f->ml.pos.y + f->ml.currentDir.x * MOV)]))
			f->ml.pos.y += f->ml.currentDir.x * MOV;
		if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.currentDir.y * MOV)][(int)f->ml.pos.y]))
			f->ml.pos.x -= f->ml.currentDir.y * MOV;
	}
	// dcha mov
	if(f->mv.d == 1)
	{
		if (ft_canmove(f->map[(int)f->ml.pos.x][(int)(f->ml.pos.y - f->ml.currentDir.x * MOV)]))
			f->ml.pos.y -= f->ml.currentDir.x * MOV;
		if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.currentDir.y * MOV)][(int)f->ml.pos.y]))
			f->ml.pos.x += f->ml.currentDir.y * MOV;
	}
	printf("pos[%f][%f]\n", f->ml.pos.x,f->ml.pos.y);
	return(0);
}

int ft_key_press(int key, t_file *f)
{
	if (key == KEY_ESC) // TODO: salida segura del programa sin leaks
		exit(0);
	if(key == KEY_W)
		f->mv.w = 1;
	if(key == KEY_LEFT)
		f->mv.l = 1;
	if(key == KEY_S)
		f->mv.s = 1;
	if(key == KEY_RIGHT)
		f->mv.r = 1;
	if(key == KEY_D)
		f->mv.d = 1;
	if(key == KEY_A)
		f->mv.a = 1;
	return(0);
}

int ft_key_release(int key, t_file *f)
{
	if (key == KEY_ESC) // TODO: salida segura del programa sin leaks
		exit(0);
	if(key == KEY_W)
		f->mv.w = 0;
	if(key == KEY_RIGHT)
		f->mv.r = 0;
	if(key == KEY_S)
		f->mv.s = 0;
	if(key == KEY_LEFT)
		f->mv.l = 0;
	if(key == KEY_D)
		f->mv.d = 0;
	if(key == KEY_A)
		f->mv.a = 0;
	return (0);
}

int ft_move_and_draw(t_file *f)
{
	ft_check_and_move(f);
	ft_initraycast(f);
	mlx_put_image_to_window(f->ml.mlx, f->ml.window, f->ml.frame.img, 0, 0);
}