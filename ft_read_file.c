/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 03:59:29 by dgomez            #+#    #+#             */
/*   Updated: 2020/03/30 12:34:31 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	ft_set_res(char **res, int j, t_file *f)
{
	if (j == 1)
		f->w = ft_atoi(res[j]);
	if (j == 2)
		f->h = ft_atoi(res[j]);
}

int			ft_handle_resolution(t_file *f)
{
	char	**res;
	int		i;
	int		j;

	if (*f->line == 'R' && *f->line)
	{
		i = 0;
		j = 1;
		res = ft_split(f->line, ' ');
		if (res[3] != 0)
			return (f->rtn = -1);
		while (j <= 2)
		{
			while (res[j][i])
			{
				if (!ft_isdigit(res[j][i]))
					return (f->rtn = -1);
				i++;
			}
			i = 0;
			ft_set_res(res, j, f);
			j++;
		}
	}
	return (f->rtn);
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
		ft_handle_error("Path of Texture is invalid\n");
	if (ft_check_extension((ext = ft_strchr(++aux, '.'))) < 0)
		ft_handle_error("The extension of Texture file is invalid\n");
	if ((f->texture[i] = open(--aux, O_RDONLY)) < 0)
		ft_handle_error("Error at opening Texture file\n");
	else
	{
		f->ml.text[i].img = mlx_xpm_file_to_image(f->ml.mlx, aux,
			&f->ml.text[i].width, &f->ml.text[i].height);
		f->ml.text[i].data = (int*)mlx_get_data_addr(f->ml.text[i].img,
			&f->ml.text[i].bits_per_pixel,
			&f->ml.text[i].size_line, &f->ml.text[i].endian);
	}
	while (*f->line)
		f->line++;
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
	while (*f->line)
		f->line++;
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

static int	localisdigit(t_file *f, char **test)
{
	int		i;
	int		j;
	char	**aux;

	aux = test;
	i = 0;
	j = 0;
	while (i <= 2)
	{
		j = 0;
		while (aux[i][j])
		{
			if (!ft_isdigit(aux[i][j]))
				return ((f->rtn = -1));
			j++;
		}
		j = 0;
		i++;
	}
	return (f->rtn);
}

static int	localstrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
			i++;
		s++;
	}
	return (i);
}

int			ft_handle_cfloor(t_file *f)
{
	char **test;
	char **test2;

	if (*f->line == 'F' && *f->line)
	{
		test = ft_split(f->line, ' ');
		test2 = ft_split(test[1], ',');
		if (localisdigit(f, test2) == -1 || localstrchr(test[1], ',') > 2
			|| test2[3] != 0 || test[2] != 0)
			return ((f->rtn = -1));
		if ((f->cf[0] = ft_atoi(test2[0])) >= 0)
			if (f->cf[0] > 255 || f->cf[0] < 0)
				return ((f->rtn = -1));
		if ((f->cf[1] = ft_atoi(test2[1])) >= 0)
			if (f->cf[1] > 255 || f->cf[1] < 0)
				return ((f->rtn = -1));
		if ((f->cf[2] = ft_atoi(test2[2])) >= 0)
			if (f->cf[2] > 255 || f->cf[2] < 0)
				return ((f->rtn = -1));
	}
	return (f->rtn);
}

int			ft_handle_croof(t_file *f)
{
	char **test;
	char **test2;

	if (*f->line == 'C' && *f->line)
	{
		test = ft_split(f->line, ' ');
		test2 = ft_split(test[1], ',');
		if (localisdigit(f, test2) == -1 || localstrchr(test[1], ',') > 2
			|| test2[3] != 0 || test[2] != 0)
			return ((f->rtn = -1));
		if ((f->cc[0] = ft_atoi(test2[0])) >= 0)
			if (f->cc[0] > 255 || f->cc[0] < 0)
				return ((f->rtn = -1));
		if ((f->cc[1] = ft_atoi(test2[1])) >= 0)
			if (f->cc[1] > 255 || f->cc[1] < 0)
				return ((f->rtn = -1));
		if ((f->cc[2] = ft_atoi(test2[2])) >= 0)
			if (f->cc[2] > 255 || f->cc[2] < 0)
				return ((f->rtn = -1));
	}
	return (f->rtn);
}

int			ft_handle_rgb(t_file *f, int i)
{
	char	*tmp;
	char	*aux;
	char	**color;
	int		*rgb;

	if (i == 1)
	{
		color = &f->c_f;
		rgb = f->cf;
	}
	else if (i == 2)
	{
		color = &f->c_c;
		rgb = f->cc;
	}
	i = 0;
	while (i < 3)
	{
		tmp = ft_dec2hex((unsigned long)rgb[i]);
		if (i == 0)
			*color = ft_strdup(tmp);
		else
		{
			aux = ft_strjoin(*color, tmp);
			free(*color);
			*color = aux;
		}
		i++;
	}
	return (f->rtn);
}

int			ft_handle_map_read(t_file *f)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
	{
		i = ft_strlen(f->line); // tamaño de la linea(num columnas)
		if (f->buff == NULL)
			temp = ft_strdup(f->line);
		else
			temp = ft_strjoin(f->buff, f->line);
		free(f->buff);
		f->buff = temp;
		temp = ft_strjoin(f->buff, "\n");
		free(f->buff);
		f->buff = temp;
		if (f->nColMax == 0 || f->nColMax < i)
			f->nColMax = i;
		f->nFil++;
	}
	return (f->rtn);
}

static void	ft_filling_matrix(t_file *f, int k, int i, int j)
{
	if (f->buff[k] == '0' || f->buff[k] == '1' || f->buff[k] == '2')
	{
		f->map[i][j] = (int)f->buff[k] - '0';
	}
	else if (f->buff[k] == ' ')
	{
		f->map[i][j] = 4;
	}
	else if (f->buff[k] == 'N' || f->buff[k] == 'S' || f->buff[k] == 'E'
		|| f->buff[k] == 'W')
	{
		if (f->dir == '\0')
		{
			f->map[i][j] = 0;
			f->dir = f->buff[k];
			ft_cast_init_dir(f);
			f->pos[0] = i;
			f->ml.pos.x = i;
			f->pos[1] = j;
			f->ml.pos.y = j;
		}
	}
}

int			alloc_map(t_file *f)
{
	int i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!(f->map = ft_calloc(f->nFil, sizeof(int *))))
		return (0);
	else
	{
		while (i[0] < f->nFil && f->buff[i[2]])
		{
			if (!(f->map[i[0]] = ft_calloc(f->nColMax, sizeof(int *))))
				return (0);
			i[1] = 0;
			while (i[1] < f->nColMax && f->buff[i[2]] != '\n')
			{
				ft_filling_matrix(f, i[2], i[0], i[1]);
				i[2]++;
				i[1]++;
			}
			i[2]++;
			i[0]++;
		}
	}
	return (0);
}

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
