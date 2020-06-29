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

#include"cub3d.h"

void  ft_cast_init_dir(t_file *f)
{
    if (f->dir == 'N')
    {
        f->ml.currentDir.x = 0.0; 
        f->ml.currentDir.y = 1.0;
    }
    else if (f->dir == 'E')
    {
        f->ml.currentDir.x = 1.0;
        f->ml.currentDir.y = 0.0;
    }
    else if(f->dir == 'S')
    {
        f->ml.currentDir.x = 0.0;
        f->ml.currentDir.y = -1.0;
    }
    else
    {
        f->ml.currentDir.x = -1.0;
        f->ml.currentDir.y = 0.0;
    }
}

void    ft_calc_step(t_file *f)
{
    if (f->ml.ray.x < 0)
    {
        f->ml.step[0] = -1;
        f->ml.raylength.x = (f->ml.Pos.x - f->ml.mapX) * f->ml.deltaDist.x;
    }
    else
    {
        f->ml.step[0] = 1;
        f->ml.raylength.x = (f->ml.mapX + 1.0 - f->ml.Pos.x) * f->ml.deltaDist.x;
    }
    if (f->ml.ray.y < 0)
    {
        f->ml.step[1] = -1;
        f->ml.raylength.y = (f->ml.Pos.y - f->ml.mapY) * f->ml.deltaDist.y;
    }
    else
    {
        f->ml.step[1] = 1;
        f->ml.raylength.y = (f->ml.mapY + 1.0 - f->ml.Pos.y) * f->ml.deltaDist.y;
    }
}

void    ft_calc_side(t_file *f, int *side)
{
    if (f->ml.raylength.x < f->ml.raylength.y)
    {
        f->ml.raylength.x += f->ml.deltaDist.x;
        f->ml.mapX += f->ml.step[0];
        *side = 0;
    }
    else
    {
        f->ml.raylength.y += f->ml.deltaDist.y;
        f->ml.mapY += f->ml.step[1];
        *side = 1;
    }
}

int     ft_initraycast(t_file *f)
{
    int x;
    int hit;
    int side;
    ft_cast_init_dir(f);
    while(1) //Game loop
    {
        x = -1;
        while (++x <= f->w) // raycast
        {
            // posicion en la matriz
            f->ml.mapX = f->current_pos[0];
            f->ml.mapY = f->current_pos[1];
            // posicion vectorial
            f->ml.Pos.x = (double)f->ml.mapX;
            f->ml.Pos.y = (double)f->ml.mapY;
            hit = 0;
            // plano de camera 
            f->ml.cameraX = (2 * x / (double)f->w) -1;
            f->ml.ray.x = f->ml.currentDir.x + f->ml.plane.x * f->ml.cameraX;
            f->ml.ray.y = f->ml.currentDir.y + f->ml.plane.y * f->ml.cameraX;
            f->ml.deltaDist.x = (f->ml.ray.y == 0) ? 0: ((f->ml.ray.x == 0) ? 1 : abs(1 / f->ml.ray.x));
            f->ml.deltaDist.y = (f->ml.ray.x == 0) ? 0: ((f->ml.ray.y == 0) ? 1 : abs(1 / f->ml.ray.y));
            // calc step
            ft_calc_step(f);
            // perform DDA
            while (hit == 0)
            {
                ft_calc_side(f, &side);
                if (f->map[f->ml.mapX][f->ml.mapY] == 2 || f->map[f->ml.mapX][f->ml.mapY] == 1)
                {
                    printf("CHOQUE: [%d , %d]", f->ml.mapX, f->ml.mapY);
                    hit = 1;
                }
            }
        }
        // TODO: mlx_hook(f->ml.window, 2, 1, ft_handle_movement, &f);
    }
}