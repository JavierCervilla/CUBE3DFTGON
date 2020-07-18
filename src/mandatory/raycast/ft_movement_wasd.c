/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement_wasd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:08:51 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 04:34:47 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int		ft_canmove(int x)
{
	if (x == 1 || x == 2)
		return (0);
	else
		return (1);
}

void	ft_move_l(t_file *f)
{
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y + f->ml.dir.x * MOV)]))
		f->ml.pos.y += f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.dir.y * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x -= f->ml.dir.y * MOV;
}

void	ft_move_r(t_file *f)
{
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y - f->ml.dir.x * MOV)]))
		f->ml.pos.y -= f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.dir.y * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x += f->ml.dir.y * MOV;
}

void	ft_move_up(t_file *f)
{
	if (ft_canmove(f->map[(int)(f->ml.pos.x + f->ml.dir.x * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x += f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y + f->ml.dir.y * MOV)]))
		f->ml.pos.y += f->ml.dir.y * MOV;
}

void	ft_move_dwn(t_file *f)
{
	if (ft_canmove(f->map[(int)(f->ml.pos.x - f->ml.dir.x * MOV)]
		[(int)f->ml.pos.y]))
		f->ml.pos.x -= f->ml.dir.x * MOV;
	if (ft_canmove(f->map[(int)f->ml.pos.x]
		[(int)(f->ml.pos.y - f->ml.dir.y * MOV)]))
		f->ml.pos.y -= f->ml.dir.y * MOV;
}
