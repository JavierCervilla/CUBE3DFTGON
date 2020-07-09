/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2020/03/30 12:42:33 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Paso 1, leer la resolución:
	posibles errores:
		No existe R
		No puede haber negativos
		Más de dos números || menos de dos números
		mayor que 200px y < 1920 para el ancho
		mayor que 200px y < 1080px para el alto
	Paso 2, leer texturas y guardarlas en un array
	$dir = [NO, SO, WE, EA]
	posibles errores:
		no encuentra $dir[x]
		no encuentra "./"
		Intenta abrir el archivo, crea un array de FD si son válidos
	Paso 3, leer el Sprite
	par amanejar varios archivos tendremos la funcion get_sprites()
	que guarda los FD válidos en un array de enteros. Si existe un invalido
	exit(0);
	posibles errores:
		No encunetra S
		que no encuentra el ./
		que no pueda abrir el archivo de la dirección
		que la extensión de archivos no sea imagen
	Paso 4, leer el color Floor
		hacemo atoi hasta la coma, miramos que el numero sea
		> 0 y < 255, si eso es verdad, le hacemos ft_dec_hex a cada numero
		posibles errores:
			si hay mas de tres numeros, error.
			que alguno de los nuero sea < 0 o > 255
			que sean menos de tres numeros
	Paso 5, leer el color Cielo
		mismas condiciones de paso 4
	Paso 6, leer el mapa
		el mapa sabemos que puede contener 4 caracteres:
			0				espacio vacio
			1				muros
			2				objeto / sprite
			[N, S, E, W]	orientacion inicial del jugador
		posibles errores:
			solo puede tener una sola letra de las validas.
			el mapa debe estar encerrado x muros(1)
				·para comprobar esto utilizamos el algoritmo de flood filling


* */

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
	// Estructura auxiliar mlx
	f->ml.pos.x = 0.0;
	f->ml.pos.y = 0.0;
	f->ml.currentDir.x = 0.0; 
    f->ml.currentDir.y = 0.0;
	f->ml.plane.x = 0.0; 
    f->ml.plane.y = 0.0;
	f->ml.side = 0;
	f->ml.ray.x = 0;
	f->ml.ray.y = 0;
	f->ml.deltaDist.x = 0;
	f->ml.deltaDist.y = 0;
	f->ml.raylength.x = 0;
	f->ml.raylength.y = 0;
	f->ml.step.x = 0;
	f->ml.step.y = 0;
	f->ml.cameraX = 0;
	f->ml.map.x = 0;
	f->ml.map.y = 0;
	f->ml.lineHeight = 0;
	f->ml.perpWallDist = 0;
	f->ml.drawStart = 0;
	f->ml.drawEnd = 0;
	f->ml.side = 0;
	f->ml.x = 0;
	f->ml.t_side = 0;
	f->ml.textx = 0;
	f->ml.textY = 0;
	f->ml.textStep = 0.0;
	
	// EStructura mov
	f->mv.a = 0;
	f->mv.d = 0;
	f->mv.l = 0;
	f->mv.r = 0;
	f->mv.s = 0;
	f->mv.w = 0;
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
	//debugging(&f);
	//  declarar la imagen y obtener la data de la imagen
	f.ml.frame.img = mlx_new_image(f.ml.mlx, f.w, f.h);
	f.ml.frame.data = (int*)mlx_get_data_addr(f.ml.frame.img, &f.ml.bitspp, &f.ml.size_line, &f.ml.end);
	ft_initraycast(&f);
	mlx_hook(f.ml.window, 2, 1, ft_key_press, &f);
	mlx_hook(f.ml.window, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.ml.mlx, ft_move_and_draw, &f);
	mlx_loop(f.ml.mlx);
	return (0);
}
