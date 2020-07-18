/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:29:52 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 17:51:22 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int			ft_check_extension(char *str)
{
	char	*extensions;
	int		rtn;

	rtn = -1;
	extensions = ".xpm";
	if (ft_strcmp(extensions, str) != 0)
		rtn = 1;
	return (rtn);
}

int			ft_handle_path_texture(t_file *f, int i)
{
	char	*aux;
	char	*ext;

	if (!(f->line = ft_strchr(f->line, '.')))
		ft_handle_error("Path of Texture is invalid\n");
	else if (*(f->line + 1) == '/')
		aux = ft_strdup(f->line);
	else
		f->rtn = 1;
	if (ft_check_extension((ext = ft_strchr(++aux, '.'))) < 0)
		ft_handle_error_aux("The extension of Texture file is invalid\n", aux);
	if ((f->texture[i] = open(--aux, O_RDONLY)) < 0)
		ft_handle_error_aux("Error at opening Texture file\n", aux);
	else
	{
		f->ml.text[i].img = mlx_xpm_file_to_image(f->ml.mlx, aux,
			&f->ml.text[i].width, &f->ml.text[i].height);
		f->ml.text[i].data = (int*)mlx_get_data_addr(f->ml.text[i].img,
			&f->ml.text[i].bits_per_pixel,
			&f->ml.text[i].size_line, &f->ml.text[i].endian);
		close(f->texture[i]);
	}
	free(aux);
	return (f->rtn);
}

int			ft_handle_path_spritex(t_file *f, int i)
{
	char	*aux;
	char	*ext;

	if (!(f->line = ft_strchr(f->line, '.')))
		ft_handle_error("Path of Spritex is invalid\n");
	else if (*(f->line + 1) == '/')
		aux = ft_strdup(f->line);
	else
		ft_handle_error("Path of Spritex is invalid\n");
	if (ft_check_extension((ext = ft_strchr(++aux, '.'))) < 0)
		ft_handle_error("The extension of Spritex file is invalid\n");
	if ((f->sprite = open(--aux, O_RDONLY)) < 0)
		ft_handle_error("Error at opening Spritex file\n");
	else
	{
		f->ml.text[4].img = mlx_xpm_file_to_image(f->ml.mlx, aux,
			&f->ml.text[4].width, &f->ml.text[4].height);
		f->ml.text[4].data = (int*)mlx_get_data_addr(f->ml.text[4].img,
			&f->ml.text[4].bits_per_pixel,
			&f->ml.text[4].size_line, &f->ml.text[4].endian);
		close(f->sprite);
	}
	free(aux);
	return (f->rtn);
}

int			ft_handle_textures(t_file *f)
{
	while (*f->line)
	{
		if (*f->line == 'N' && *(f->line + 1) == 'O')
			if (ft_handle_path_texture(f, 0) == -1)
				ft_handle_error("Text NO ERROR");
		if (*f->line == 'S' && *(f->line + 1) == 'O')
			if (ft_handle_path_texture(f, 1) == -1)
				ft_handle_error("Text SO ERROR");
		if (*f->line == 'W' && *(f->line + 1) == 'E')
			if (ft_handle_path_texture(f, 2) == -1)
				ft_handle_error("Text WE ERROR");
		if (*f->line == 'E' && *(f->line + 1) == 'A')
			if (ft_handle_path_texture(f, 3) == -1)
				ft_handle_error("Text EA ERROR");
		if (*f->line)
			f->line++;
	}
	return (f->rtn);
}

int			ft_handle_spritex(t_file *f)
{
	int i;

	i = 0;
	if (!*f->line && (f->texture[0] >= 3 && f->texture[1] > f->texture[0]
		&& f->texture[2] > f->texture[1]) && !f->sprite)
		f->line++;
	while (*f->line)
	{
		if (*f->line == 'S' && *(f->line + 1) == ' ')
			if (ft_handle_path_spritex(f, i) == -1)
				ft_handle_error("Text S ERROR");
		if (*f->line)
			f->line++;
	}
	return (f->rtn);
}
