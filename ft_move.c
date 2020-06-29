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

void ft_print_map(t_file *f)
{
	int k = 0;
	int j = 0;

	system("clear");
	while (j < f->nFil)
    {
        k = 0;
        while (k < f->nColMax)
        {
            ft_printf("|%2d", f->map[j][k]);
            k++;
        }
        ft_printf("|\n");
        j++;
    }
}

int ft_check_and_move(int dir, t_file *f)
/*
**	dir = 1 -> movimiento hacia delate, N fil - 1
**	dir = 2 -> movimiento hacia derecha, E col + 1
**	dir = 3 -> movimiento hacia abajo, S fil + 1
**	dir = 4 -> movimiento hacia izquierda, W col - 1
*/
{
	if (dir == 1)
	{
		if(f->map[f->current_pos[0] - 1][f->current_pos[1]] == 3)
		{
			f->current_pos[0] = f->current_pos[0] - 1;
			ft_printf("UP!!!\n");
			return(0);
		}
	}
	else if (dir == 2)
	{
		if(f->map[f->current_pos[0]][f->current_pos[1] + 1] == 3)
		{
			f->current_pos[1] = f->current_pos[1] + 1;
			ft_printf("RIGHT!!!!\n");
			return(0);
		}
	}
	else if (dir == 3)
	{
		if(f->map[f->current_pos[0] + 1][f->current_pos[1]] == 3)
		{
			f->current_pos[0] = f->current_pos[0] + 1;
			ft_printf("DOWN!!!\n");
			return(0);
		}
	}
	else if (dir == 4)
	{
		if(f->map[f->current_pos[0]][f->current_pos[1] - 1] == 3)
		{
			f->current_pos[1] = f->current_pos[1] - 1;
			ft_printf("LEFT!!!\n");
			return(0);
		}
	}
	return(0);
}

int ft_handle_movement(int key, t_file *f)
{
	if (key == KEY_ESC)
		exit(0);
	else if(key == KEY_W || key == KEY_UP)
		ft_check_and_move(1, f);
	else if(key == KEY_D || key == KEY_RIGHT)
		ft_check_and_move(2, f);
	else if(key == KEY_S || key == KEY_DOWN)
		ft_check_and_move(3, f);
	else if(key == KEY_A || key == KEY_LEFT)
		ft_check_and_move(4, f);
	printf("pos[%d][%d]\n", f->current_pos[0], f->current_pos[1]);
}

