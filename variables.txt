# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    variables.txt                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#              #
#    Updated: 2020/07/18 19:02:01 by jcervill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/Xlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include "includes/minilibx-linux/mlx.h"
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

# define ROT 0.14
# define MOV 0.14
/*-------------ESTRUCTURA SAVE---------------------*/

typedef struct		s_save
{
	unsigned int	file_size;
	unsigned char	reserved1;
	unsigned char	reserved2;
	unsigned int	offset_bits;
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bmp;

/*-------------ESTRUCTURA IMG----------------------*/

typedef struct		s_img
{
	void			*img;						// instancia de la imagen
	int				*data;						// data de la imagen
	int				width;						// ancho de la textura
	int				height;						// alto de la textura
	int				bits_per_pixel;				// bits per pixel
	int				size_line;					// tamaño de linea
	int				endian;						// endian
}					t_img;

/*-------------ESTRUCTURA VECTOR-------------------*/

typedef struct		s_vector
{
	double			x;									// componente x
	double			y;									// componente y
}					t_vector;

/*------------ESTRUCRTURA SPRITE-------------------*/

typedef struct		s_sprite
{
	t_vector		pos;						// posicion del sprite en el mapa
	t_vector		cam_pos;					// posicion del sprite en relacion conm la camara
	double			distance;					// distancia del sprite con el jugador
	int				used;						// indica is el sprite ya ha sido pintado
}					t_sprite;



/*-------------ESTRUCTURA AUX MLX------------------*/

typedef struct		s_mlx
{
	int				bitspp;						// bits por pixel (mlx: get data addr)
	int				size_line;					// tamaño de line (mlx: get data addr)
	int				end;						// end (mlx: get data addr)
	void			*mlx;						// instancia de mlx
	void			*window;					// instancia de ventana
	t_vector		plane;						// camera plane
	t_vector		pos;						// posicion actual
	t_vector		dir;						// direccion del
	t_vector		ray;						// rayo 
	t_vector		deltadist;					// distancia entre xs o ys 
	t_vector		raylength;					// distancia del rayo
	t_vector		step;						// ray components -1 if neg +1 if pos
	t_vector		map;						// cuadro del mapa: X Columnas, Y Filas
	
	/*-------SPRITES-------------------*/
	
	double			*zbuff;						// buffer profundidad
	t_sprite		*sp;						// array de estructuras de sprites
	int				*sp_order;					// array de index ordenados
	t_vector		transform;					// transform del sprite
	double			inv_det;					// inversa para transform
	int				sp_screen_x;
	int				sp_height;					// altura del sprite
	int				sp_width;					// ancho del sprite
	int				start_sp_x;					// draw start x
	int				start_sp_y;					// draw start y
	int				end_sp_x;					// draw end x
	int				end_sp_y;					// draw end y
	int				tex_x;						// texture x
	int				tex_y;						// texture y
	/*----------------------------------*/
	double			camerax;					// coordenada x en camera
	int				lineheight;					// altura de la linea a dibujar
	double			perpwalldist;				// distancia ortogonal
	int				drawStart;					// primer pixel donde tiene que pintar
	int				drawend;					// ultimo pixel a pintar
	int				color;						// color de los muros
	int				x;							// contador para el bucle
	int				side;						// side del muro
	t_img			frame;						// frame de pantalla, se pushea a la window
	t_img			text[5];					// array de imagenes de texturas:
												//   [0] NO ./north_texture [1] SO ./south_texture
												//   [2] WE ./west_texture  [3] EA ./east_texture
												//	 [4] S textura sprite
	int				t_side;						// indice de textura
	double			wallx;						// punto exacto donde golpea el rayo
	int				textx;						// columnas dentro de texturas
	int				texty;						// filas dentro de texturas
	double			textstep;					// paso de coordenadas por pixel
	double			textpos;					// posicion de la textura
}					t_mlx;

/*--------------ESTRUCTURA AUX MOVIMIENTO---------*/

typedef struct		s_mov
{
	int				a;							// movimiento izquierda
	int				s;							// movimiento abajo
	int				w;							// movimiento alante
	int				d;							// movimiento derecha
	int				r;							// rotacion derecha
	int				l;							// rotacion izquierda
}					t_mov;

/*--------------ESTRUCTURA PRINCIPAL--------------*/

typedef struct		s_readfile
{
	int				fd;							//  FD del Mapa.
	int				w;							//  Ancho de Pantalla.
	int				h;							//  Alto de pantalla.
	int				texture[4];					//  Array de FD de Texturas.
												//   [0] NO ./north_texture [1] SO ./south_texture[2]
												//   WE ./west_texture [3] EA ./east_textur
	int				sprite;						//  FD de Spritex.
	char			*line;						//  Linea leida por el GNL.
	int				c_f;						//  Colores suelo hex
	int				cf[3];						//  colores del suelo en formato rgb.
	int				c_c;						//  colores del techo en formato hex.
	int				cc[3];
	int				**map;						//  Matriz de mapa
	char			dir;						//  orientacion del jugador
	int				pos[2];						//	posicion inical del jugador
	int				mapreaded;					//  -1 si no se ha leido 0 si se termino de leer
	int				ncolmax;					//  Numero de columnas MAX
	int				nfil;						//  Numero de filas
	char			*buff;						//  Buff auxiliar para guardar el mapa;
	int				rtn;						//  retorno para funciones, -1 = ERROR
	int				sprite_num;					//  numero de sprites
	int				save;						//  flag para guardar
	/*---------------ESTRUCTURAS AUXILIARES-------------------------*/
	t_sprite		*spr;						// array de estructuras de sprite
	t_mlx			ml;							// estructura auxiliar para instancias de mlx
	t_mov			mv;							// estructura auxiliar para los movimientos, cada vez que se genera un evento se crea esta estructura
}					t_file;


/*
** errors
*/

void				ft_handle_error_aux(char *str, void *aux);
void				ft_handle_error_ptr(char *str, void ***aux);
void				ft_handle_error(char *str);
void				ft_free(void ***ptr);

/*
** ft_read_src_file(); utils
*/

int					ft_read(t_file *f);
int					ft_read_src_file(t_file *f);
int					ft_read_src_file2(t_file *f);
int					ft_handle_resolution(t_file *f);
int					ft_handle_textures(t_file *f);
int					ft_check_extension(char *str);
int					ft_handle_spritex(t_file *f);
int					ft_handle_rgb(t_file *f);
int					alloc_map(t_file *f);
int					ft_map_check(int row, int col, t_file *f);
int					ft_handle_croof(t_file *f);
int					ft_handle_cfloor(t_file *f);
int					ft_handle_map_read(t_file *f);



/*
** RAY CASTER ENGINE
*/

int					ft_initraycast(t_file *f);
int					ft_exit_game(t_file *f);
void				ft_init_rc(t_file *f);
void				ft_fixing_def(t_file *f);
void				ft_init_mlx_struct(t_file *f);
void				ft_init_mlx_struct2(t_file *f);
void				ft_init_file_struct(t_file *f);
void				ft_init_file_struct2(t_file *f);
void				ft_calc_step(t_file *f);
void				ft_calc_side(t_file *f);

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
void				ft_move_l(t_file *f);
void				ft_move_r(t_file *f);
void				ft_rot_l(t_file *f, double dirxaux, double planexaux);
void				ft_rot_r(t_file *f, double dirxaux, double planexaux);
void				ft_move_dwn(t_file *f);
void				ft_move_up(t_file *f);
int					ft_canmove(int x);

/*
**	SPRITES
*/

void				ft_sprite(t_file *f);
void				ft_init_sp(t_file *f);
void				ft_calc_rel_dist(t_file *f);

/*
** SAVE
*/

void				ft_init_bmp_header(t_file *f, t_bmp *bmp);
void				ft_create_bmp(t_file *f);

#endif
