/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2020/07/18 18:34:52 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void		ft_check_file(t_file *f, char *file)
{
	int		len;
	char	*ext;

	len = ft_strlen_int(file);
	if (len <= 5)
		ft_handle_error("ERROR DE FORMATO DE ARCHIVO\n");
	else
	{
		ext = ft_substr(file, len - 4, 4);
		if (ft_strcmp(ext, ".cub") != 4)
			ft_handle_error("ERROR DE EXTENSION\n");
		else
		{
			if ((f->fd = open(file, O_RDONLY)) <= 0)
				ft_handle_error("ERROR AL ABRIR EL ARCHIVO\n");
		}
		free(ext);
	}
}

void		ft_check_args(t_file *f, int argc, char *argv[])
{
	char *aux;

	if (argc == 2)
	{
		aux = argv[1];
		ft_check_file(f, aux);
		f->save = 0;
	}
	else if (argc == 3)
	{
		aux = argv[1];
		if (ft_strcmp(argv[2], "--save") == 6 && ft_strlen_int(argv[2]) == 6)
		{
			ft_check_file(f, aux);
			f->save = 1;
		}
		else
			ft_handle_error("ERROR DE SEGUNDO ARGUMENTO\n");
	}
	else
		ft_handle_error("ERROR DE ARGUMENTOS\n");
}

int			ft_exit_game(t_file *f)
{
	int i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(f->ml.mlx, f->ml.text[i].img);
		f->ml.text[i].img = NULL;
		i++;
	}
	mlx_destroy_image(f->ml.mlx, f->ml.frame.img);
	f->ml.frame.img = NULL;
	mlx_destroy_window(f->ml.mlx, f->ml.window);
	if (f->mapreaded == 1)
	{
		i = -1;
		while (f->map[++i] != NULL)
			free(f->map[i]);
		free(f->map);
	}
	free(f->buff);
	free(f->ml.zbuff);
	f->map = NULL;
	f->buff = NULL;
	f->ml.zbuff = NULL;
	exit(0);
}

int			main(int argc, char *argv[])
{
	t_file f;

	ft_check_args(&f, argc, argv);
	if (!(f.ml.mlx = mlx_init()))
		ft_handle_error("ERROR.MLX_INIT");
	if (ft_read(&f) == -1)
		ft_handle_error("ERROR.Lectura del archivo");
	if (!(f.ml.window = mlx_new_window(f.ml.mlx, f.w, f.h, "CUB3D")))
		ft_handle_error("ERROR.MLX_WINDOW");
	f.ml.frame.img = mlx_new_image(f.ml.mlx, f.w, f.h);
	f.ml.frame.data = (int *)mlx_get_data_addr(f.ml.frame.img,
		&f.ml.bitspp, &f.ml.size_line, &f.ml.end);
	ft_init_sp(&f);
	ft_initraycast(&f);
	ft_sprite(&f);
	if (f.save == 1)
		ft_create_bmp(&f);
	mlx_hook(f.ml.window, 2, 1, ft_key_press, &f);
	mlx_hook(f.ml.window, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.ml.mlx, ft_move_and_draw, &f);
	mlx_hook(f.ml.window, 17, 1L << 17, ft_exit_game, &f);
	mlx_loop(f.ml.mlx);
	return (0);
}
