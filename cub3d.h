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

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/Xlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
//# include <X11/extensions/XShm.h>
//# include "includes/mlx/mlx.h"
# include "includes/minilibx_linux/mlx.h"
# include "includes/printf/ft_printf.h"
/*----------TECLAS_KEYCODE---------*/
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_C 99
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
# else
#  define KEY_ESC 53
#  define KEY_C 8
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
# endif


/*-------------CONSTANTES--------------------------*/

# define ROT 0.04
# define MOV 0.04

/*-------------ESTRUCTURA IMG----------------------*/

typedef struct		s_img
{
	void	*img;					// instancia de la imagen
	int		*data;					// data de la imagen
	int		width;					// ancho de la textura
	int		height;					// alto de la textura
	int		*bits_per_pixel;		// bits per pixel
	int		*size_line;				// tamaño de linea
	int		*endian;				// endian
}					t_img;


/*-------------ESTRUCTURA VECTOR-------------------*/

typedef struct		s_vector
{
	double	x;					// componente x
	double	y;					// componente y
}					t_vector;


/*-------------ESTRUCTURA AUX MLX------------------*/

typedef struct		s_mlx
{
	void		*img;					// instancia de la imagen de mlx
	int			*data_img;				// data de imagen
	int			bitspp;					// bits por pixel (mlx: get data addr)
	int			size_line;				// tamaño de line (mlx: get data addr)
	int			end;					// end (mlx: get data addr)
	void		*mlx;					// instancia de mlx
	void		*window;				// instancia de ventana
	t_vector	plane;					// camera plane
	t_vector	pos;					// posicion actual
	t_vector	currentDir;				// direccion del
	t_vector	ray;					// rayo 
	t_vector	deltaDist;				// distancia entre xs o ys 
	t_vector	raylength;				// distancia del rayo
	t_vector	step;					// ray components -1 if neg +1 if pos
	double		cameraX;				// coordenada x en camera
	int			mapX;					// cuadrado en el que estas componete x
	int			mapY;					// cuadrado en el que estas componete x
	int			lineHeight;				// altura de la linea a dibujar
	double		perpWallDist;			// distancia ortogonal
	int			drawStart;				// primer pixel donde tiene que pintar
	int			drawEnd;				// ultimo pixel a pintar
	int			color;					// color de los muros
	int			x;						// contador para el bucle
	int			side;					// side del muro
	t_img		texture[4];				// array de imagenes de texturas.
}					t_mlx;

/*--------------ESTRUCTURA AUX MOVIMIENTO---------*/
typedef struct		s_mov
{
	int	a;						// movimiento izquierda
	int	s;
	int	w;
	int	d;
	int r;
	int l;
}					t_mov;

/*--------------ESTRUCTURA PRINCIPAL--------------*/

typedef struct		s_readfile
{
	int		fd;					//  FD del Mapa.
	int		w;					//  Ancho de Pantalla.
	int		h;					//  Alto de pantalla.
	int		texture[4];			//  Array de FD de Texturas.
								//   [0] NO ./north_texture [1] SO ./south_texture[2]
								//   WE ./west_texture [3] EA ./east_textur
	int		sprite;				//  FD de Spritex.
	char	*line;				//  Linea leida por el GNL.
	char	*c_f;				//  Colores suelo hex
	int		cf[3];				//  colores del suelo en formato rgb.
	char	*c_c;				//  colores del techo en formato hex.
	int		cc[3];
	int		**map;				//  Matriz de mapa
	char	dir;				//  orientacion del jugador
	int		pos[2];				//	posicion inical del jugador
	int		mapreaded;			//  -1 si no se ha leido 0 si se termino de leer
	int		nColMax;			//  Numero de columnas MAX
	int		nFil;				//  Numero de filas
	char	*buff;				//  Buff auxiliar para guardar el mapa;
	int		rtn;				//  retorno para funciones, -1 = ERROR
	/*---------------ESTRUCTURAS AUXILIARES-------------------------*/
	
	t_mlx	ml;					// estructura auxiliar para instancias de mlx
	t_mov	mv;					// estructura auxiliar para los movimientos, cada vez que se genera un evento se crea esta estructura
}					t_file;



/*
** ft_read_src_file(); utils
*/
int					ft_read(t_file *f);
int					ft_read_src_file(t_file *f);
int					ft_handle_resolution(t_file *f);
void				ft_handle_error(char *str);
int					ft_handle_textures(t_file *f);
int					ft_check_extension(char *str);
int					ft_handle_spritex(t_file *f);
void				ft_handle_colors(t_file *f);
int					ft_handle_rgb(t_file *f, int i);
int					alloc_map(t_file *f);
int					ft_map_check(int row, int col, t_file *f);

/*
** RAY CASTER ENGINE
*/
int					ft_initraycast(t_file *f);


/*
** MOVIMIENTO ARCHIVO: ft_move.c
*/

void				ft_print_map(t_file *f);
int					ft_check_and_move(t_file *f);
void				ft_draw_line(t_file *f);
void				ft_cast_init_dir(t_file *f);
int					ft_move_and_draw(t_file *f);
int					ft_key_press(int key, t_file *f);
int					ft_key_release(int key, t_file *f);

#endif
