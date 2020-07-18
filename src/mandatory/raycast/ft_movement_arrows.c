/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement_arrows.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 01:12:43 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 04:34:38 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	ft_rot_r(t_file *f, double dirxaux, double planexaux)
{
	dirxaux = f->ml.dir.x;
	planexaux = f->ml.plane.x;
	f->ml.dir.x = f->ml.dir.x * cos(-ROT) - f->ml.dir.y * sin(-ROT);
	f->ml.dir.y = dirxaux * sin(-ROT) + f->ml.dir.y * cos(-ROT);
	f->ml.plane.x = f->ml.plane.x * cos(-ROT) - f->ml.plane.y * sin(-ROT);
	f->ml.plane.y = planexaux * sin(-ROT) + f->ml.plane.y * cos(-ROT);
}

void	ft_rot_l(t_file *f, double dirxaux, double planexaux)
{
	dirxaux = f->ml.dir.x;
	planexaux = f->ml.plane.x;
	f->ml.dir.x = f->ml.dir.x * cos(ROT) - f->ml.dir.y * sin(ROT);
	f->ml.dir.y = dirxaux * sin(ROT) + f->ml.dir.y * cos(ROT);
	f->ml.plane.x = f->ml.plane.x * cos(ROT) - f->ml.plane.y * sin(ROT);
	f->ml.plane.y = planexaux * sin(ROT) + f->ml.plane.y * cos(ROT);
}
