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
        f->ml.currentDir.x = -1.0; 
        f->ml.currentDir.y = 0.0;
        f->ml.plane.x = 0;
        f->ml.plane.y = 0.66;
        }
    else if(f->dir == 'S')
    {
        f->ml.currentDir.x = 1.0;
        f->ml.currentDir.y = 0.0;
        f->ml.plane.x = 0.0;
        f->ml.plane.y = -0.66;
    }
    else if(f->dir == 'W')
    {
        f->ml.currentDir.x = 0.0;
        f->ml.currentDir.y = -1.0;
        f->ml.plane.x = -0.66;
        f->ml.plane.y = 0;
    }
    else if (f->dir == 'E')
    {
        f->ml.currentDir.x = 0.0;
        f->ml.currentDir.y = 1.0;
        f->ml.plane.x = 0.66;
        f->ml.plane.y = 0.0;
    }
}

void    ft_calc_step(t_file *f)
{
    f->ml.step.x = 0;
    f->ml.step.y = 0;
    f->ml.raylength.x = 0;
    f->ml.raylength.y = 0;

    if (f->ml.ray.x < 0)
    {
        f->ml.step.x = -1;
        f->ml.raylength.x = (f->ml.pos.x - f->ml.mapX) * f->ml.deltaDist.x;
    }
    else
    {
        f->ml.step.x = 1;
        f->ml.raylength.x = (f->ml.mapX + 1.0 - f->ml.pos.x) * f->ml.deltaDist.x;
    }
    if (f->ml.ray.y < 0)
    {
        f->ml.step.y = -1;
        f->ml.raylength.y = (f->ml.pos.y - f->ml.mapY) * f->ml.deltaDist.y;
    }
    else
    {
        f->ml.step.y = 1;
        f->ml.raylength.y = (f->ml.mapY + 1.0 - f->ml.pos.y) * f->ml.deltaDist.y;
    }
}

void    ft_calc_side(t_file *f)
{
    if (f->ml.raylength.x < f->ml.raylength.y)
    {
        f->ml.raylength.x += f->ml.deltaDist.x;
        f->ml.mapX += f->ml.step.x;
        f->ml.side = 0;
    }
    else
    {
        f->ml.raylength.y += f->ml.deltaDist.y;
        f->ml.mapY += f->ml.step.y;
        f->ml.side = 1;
    }
}

int ft_set_wall(t_file *f)
{
    if (f->ml.ray.x < 0 && f->ml.side == 0)
    {
        f->ml.color = 444128;
    }
    if (f->ml.ray.x > 0 && f->ml.side == 0)
    {
        f->ml.color = 444128;
    }
    if (f->ml.ray.y < 0 && f->ml.side == 1)
    {
        f->ml.color = 128869416;
    }
    if (f->ml.ray.y > 0 && f->ml.side == 1)
    {
        f->ml.color = 128869416;
    }
}

void    ft_color(t_file *f)
/*TODO: CAMBIAR COLOR POR CADA DIRECCION DE PARED*/
{
    if (f->map[f->ml.mapX][f->ml.mapY] == 1)
    {
        ft_set_wall(f);
    }
    if(f->map[f->ml.mapX][f->ml.mapY] == 2)
    {
        f->ml.color = 708;
    }
}

void ft_draw_line(t_file *f)
{
    int i = 0;
    while (i < f->ml.drawStart)
    {
        *(f->ml.data_img + (i * f->w) + f->ml.x) = 7719150;
        i++;
    }
    while (i <= f->ml.drawEnd)
    {
        *(f->ml.data_img + (i * f->w) + f->ml.x) = f->ml.color;  
        i++;
    }
    while (i < f->h)
    {
        *(f->ml.data_img + (i * f->w) + f->ml.x) = 7364912;
        i++;
    } 
}

int     ft_initraycast(t_file *f)
{
    //int x;          // pixel
    int hit;        // detecta la colision con el muro
    int side;       // lado del muro si es x es 0 si es y es 1

    //ft_cast_init_dir(f);
    f->ml.x = 0;
    while (f->ml.x <= f->w) // raycast
    {
        // posicion en la matriz
        f->ml.mapX = f->ml.pos.x;
        f->ml.mapY = f->ml.pos.y;
        // colision
        hit = 0;
        // plano de camera 
        f->ml.cameraX = (2 * f->ml.x / (double)f->w) -1;
        f->ml.ray.x = f->ml.currentDir.x + f->ml.plane.x * f->ml.cameraX;
        f->ml.ray.y = f->ml.currentDir.y + f->ml.plane.y * f->ml.cameraX;
        f->ml.deltaDist.x = (f->ml.ray.y == 0) ? 0: ((f->ml.ray.x == 0) ? 1 : fabs(1 / f->ml.ray.x));
        f->ml.deltaDist.y = (f->ml.ray.x == 0) ? 0: ((f->ml.ray.y == 0) ? 1 : fabs(1 / f->ml.ray.y));
        // calc step
        ft_calc_step(f);
        // perform DDA
        while (hit == 0)
        {
            ft_calc_side(f);
            if (f->map[f->ml.mapX][f->ml.mapY] == 2 || f->map[f->ml.mapX][f->ml.mapY] == 1)
                hit = 1;
        }
        // deshaciendo deformaciones de ojo de pez, proyeccion ortogonal del rAYO
        if (f->ml.side == 0)
            f->ml.perpWallDist = (f->ml.mapX - f->ml.pos.x + (1 - f->ml.step.x) / 2) / f->ml.ray.x;
        else
            f->ml.perpWallDist = (f->ml.mapY - f->ml.pos.y + (1 - f->ml.step.y) / 2) / f->ml.ray.y;
        f->ml.lineHeight = (int)(f->h / f->ml.perpWallDist);
        // calcular el pixel mas bajo y alto a pintar
        f->ml.drawStart = (-f->ml.lineHeight / 2) + f->h / 2;
        if (f->ml.drawStart < 0)
            f->ml.drawStart = 0;
        f->ml.drawEnd = (f->ml.lineHeight / 2) +  f->h / 2;
        if (f->ml.drawEnd >= f->h || f->ml.drawEnd <= 0)
            f->ml.drawEnd = f->h - 1;
        // TODO: coloreando los muros y dando intesidades distintas a cada lado del muro(x e y)
        ft_color(f);
        ft_draw_line(f);
        f->ml.x++;
    }
    mlx_put_image_to_window(f->ml.mlx, f->ml.window, f->ml.img, 0, 0);
}