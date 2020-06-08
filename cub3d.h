/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:07:03 by gmartin-          #+#    #+#             */
/*   Updated: 2020/06/08 21:38:43 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "includes/mlx/mlx.h"
# include "includes/printf/ft_printf.h"

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
	int		init[2];			//  posición inicial del jugador
	int		mapreaded;			//  -1 si no se ha leido 0 si se termino de leer
	int		nColMax;			//  Numero de columnas MAX
	int		nFil;				//  Numero de filas
	char	*buff;				//  Buff auxiliar para guardar el mapa;
	int		rtn;				//  retorno para funciones, -1 = ERROR
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
int					map_check(int row, int col, t_file *f);

#endif
