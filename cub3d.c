/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2020/07/14 00:12:33 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_file_struct(t_file *f)
{
	int i;

	i = 0;
	f->fd = 0;
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
	f->c_c = ft_strdup("");
	f->c_f = ft_strdup("");
	f->mapreaded = -1;
	f->buff = ft_strdup("");
	f->nFil = 0;
	f->nColMax = 0;
	f->dir = '\0';
	f->pos[0] = 0;
	f->pos[1] = 0;
	f->sprite = 0;
	f->sprite_num = 0;
	// EStructura mov
	f->mv.a = 0;
	f->mv.d = 0;
	f->mv.l = 0;
	f->mv.r = 0;
	f->mv.s = 0;
	f->mv.w = 0;
}

void	ft_init_mlx_struct(t_file *f)
{
	// Estructura auxiliar mlx
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
	f->ml.step.x = 0;
	f->ml.step.y = 0;
	f->ml.camerax = 0;
	f->ml.map.x = 0;
	f->ml.map.y = 0;
	f->ml.lineheight = 0;
	f->ml.perpwalldist = 0;
	f->ml.drawStart = 0;
	f->ml.drawEnd = 0;
	f->ml.side = 0;
	f->ml.x = 0;
	f->ml.t_side = 0;
	f->ml.textx = 0;
	f->ml.texty = 0;
	f->ml.textstep = 0.0;
	// SPRITES
	
}

void	ft_handle_error(char *str) //TODO:MODIFICAR STRERR
{
	ft_printf("%s", str);
	exit(0);
}

void		ft_handle_colors(t_file *f)
{
	if ((ft_handle_rgb(f, 1)) == -1)
		ft_handle_error("Text. ERROR while parsing rgb to hex\n");
	if ((ft_handle_rgb(f, 2)) == -1)
		ft_handle_error("Text. ERROR while parsing rgb to hex\n");
}

/* DEBUGGING*/
void debugging(t_file *f)
{
	int j = 0;
	int k = 0;
	printf("Res:\n	Ancho: %d\n	Alto: %d\n", f->w, f->h);
	printf("Tex:\n	fd[0]: %d\n	fd[1]: %d\n	fd[2]: %d\n	fd[3]: %d\n", f->texture[0], f->texture[1], f->texture[2], f->texture[3]);
	printf("Spritex:\n	fd: %d\n", f->sprite);
	printf("C_Floor:\n	hexa:	%s\n	c_f[0][R]: %d\n	c_f[1][G]: %d\n	c_f[2][B]: %d\n", f->c_f, f->cf[0], f->cf[1], f->cf[2]);
	printf("C_Roof:\n	hexa:	%s\n	c_c[0][R]: %d\n	c_c[1][G]: %d\n	c_c[2][B]: %d\n", f->c_c, f->cc[0], f->cc[1], f->cc[2]);
	printf("buff:\n%s\n", f->buff);
    while (j < f->nFil)
    {
        k = 0;
        while (k < f->nColMax)
        {
            printf("%2d", f->map[j][k]);
            k++;
        }
        printf("\n");
        j++;
    }
}

int	ft_read(t_file *f)
{
	int			br; //	bytes readed

	ft_init_file_struct(f);
	f->fd = open("tx.txt", O_RDONLY);// TODO:REcibir por argc argv
	while ((br = get_next_line(f->fd, &f->line)) >= 0)
	{
		if (ft_read_src_file(f) == -1)
			return (-1);
		if (br == 0)
			break;
	}
	ft_handle_colors(f);
	ft_init_mlx_struct(f);
	if (alloc_map(f) != -1)
		if (ft_map_check(f->pos[0], f->pos[1], f) == -1)
			ft_handle_error("MAP ERROR.Error al checkear el mapa");
	return (f->rtn);
}

int	main(/*int argc, char *argv[]*/)
{
	t_file		f;  //	Declarar la estructura

	if(!(f.ml.mlx = mlx_init()))
		ft_handle_error("ERROR.MLX_INIT");
	if (ft_read(&f) == -1)
		ft_handle_error("ERROR.Lectura del archivo");
	
	if(!(f.ml.window = mlx_new_window(f.ml.mlx, f.w, f.h, "CUB3D")))
		ft_handle_error("ERROR.MLX_WINDOW");

	f.ml.frame.img = mlx_new_image(f.ml.mlx, f.w, f.h);
	f.ml.frame.data = (int*)mlx_get_data_addr(f.ml.frame.img, &f.ml.bitspp, &f.ml.size_line, &f.ml.end);	
	ft_init_sp(&f);
	ft_initraycast(&f);
	ft_sprite(&f);
	mlx_hook(f.ml.window, 2, 1, ft_key_press, &f);
	mlx_hook(f.ml.window, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.ml.mlx, ft_move_and_draw, &f);
	mlx_loop(f.ml.mlx);
	return (0);
}
