/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:27:15 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 18:14:56 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/*
**	ft_read_src_file:
**	devuelve 0 por default y -1 en error.
*/

int			ft_read_src_file(t_file *f)
{
	if (!f->w && !f->h)
	{
		if ((ft_handle_resolution(f)) == -1 || f->w < 200 ||
			f->w > 1920 || f->h < 200 || f->h > 1080)
			ft_handle_error("Res. ERROR while reading file. Bitch...\n");
	}
	else if (!f->texture[0] || !f->texture[1] || !f->texture[2]
		|| !f->texture[3])
	{
		if ((ft_handle_textures(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	else if (f->sprite == 0)
	{
		if ((ft_handle_spritex(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	ft_read_src_file2(f);
	return (f->rtn);
}

int			ft_read_src_file2(t_file *f)
{
	if (f->cf[0] == -1 || f->cf[1] == -1 || f->cf[2] == -1)
	{
		if ((ft_handle_cfloor(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	else if (f->cc[0] == -1 || f->cc[1] == -1 || f->cc[2] == -1)
	{
		if ((ft_handle_croof(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	else if (f->mapreaded == -1)
	{
		if ((ft_handle_map_read(f) == -1))
			ft_handle_error("Map. ERROR while reading flie. Noob..");
	}
	return (f->rtn);
}

int			ft_read(t_file *f)
{
	int		br;
	char	*line;

	ft_init_file_struct(f);
	while ((br = get_next_line(f->fd, &line)) >= 0)
	{
		f->line = line;
		if (ft_read_src_file(f) == -1)
			return (-1);
		free(line);
		line = NULL;
		if (br == 0)
			break ;
	}
	ft_handle_rgb(f);
	ft_init_mlx_struct(f);
	if (alloc_map(f) != -1)
		if (ft_map_check(f->pos[0], f->pos[1], f) == -1)
			ft_handle_error("MAP ERROR.Error al checkear el mapa\n");
	close(f->fd);
	return (f->rtn);
}
