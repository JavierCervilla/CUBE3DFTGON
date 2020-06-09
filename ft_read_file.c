/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:07:23 by gmartin-          #+#    #+#             */
/*   Updated: 2020/06/09 19:23:51 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_extension(char *str)
{
	char	*extensions;
	int		i;
	int		rtn;

	rtn = -1;
	extensions = ".xpm";
	if (ft_strcmp(extensions, str) != 0)
		rtn = 1;
	return (rtn);
}

int	ft_handle_resolution(t_file *f)
{
	char	**test;
	int		i;
	int		ctest;

	if (*f->line == 'R' && *f->line)
	{
		ctest = 1;
		i = 0;
		test = ft_split(f->line, ' ');
		if (test[3] != 0)
			return (f->rtn = -1);
		while (ctest <= 2)
		{
			while (test[ctest][i])
			{
				if (!ft_isdigit(test[ctest][i]))
					return (f->rtn = -1);
				i++;
			}
			i = 0;
			if (ctest == 1)
				f->w = ft_atoi(test[ctest]);
			if (ctest == 2)
				f->h = ft_atoi(test[ctest]);
			ctest++;
		}
	}
	return (f->rtn);
}

int	ft_handle_path_texture(t_file *f, int i)
{
	char *aux;
	char *ext;

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
	while (*f->line)
		f->line++;
	return (f->rtn);
}

int	ft_handle_path_spritex(t_file *f, int i)
{
	char *aux;
	char *ext;

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

int	ft_handle_textures(t_file *f)
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

int	ft_handle_spritex(t_file *f)
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

int	localisdigit(t_file *f, char **test)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	j = 0;
	aux = test;
	while (i <= 2)
	{
		j = 0;
		while (aux[i][j])
		{
			if (!ft_isdigit(aux[i][j]))
				return ((f->rtn = -1));
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	return (1);
}

char	localstrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
		{
			i++;
		}
		s++;
	}
	return (i);
}

int	ft_handle_cfloor(t_file *f)
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

int	ft_handle_croof(t_file *f)
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

int	ft_handle_rgb(t_file *f, int i)
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

int	ft_handle_map_read(t_file *f)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
	{
		i = ft_strlen(f->line);
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

// TODO: REESCRIBIR CON CALLOC PARA REDUCIR LINEAS
int	alloc_map(t_file *f)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	i = 0;
	k = 0;
	if (!(f->map = ft_calloc(f->nFil, sizeof(int *))))
		return (0);
	else
	{
		while (i < f->nFil && f->buff[k])
		{
			if (!(f->map[i] = ft_calloc(f->nColMax, sizeof(int *))))
				return (0);
			j = 0;
			l = f->nColMax;
			while (j < f->nColMax && f->buff[k] != '\n')
			{
				if (f->buff[k] == '0' || f->buff[k] == '1' || f->buff[k] == '2')
				{
					f->map[i][j] = (int)f->buff[k] - '0';
					k++;
					//l--;
				}
				else if (f->buff[k] == ' ')
				{
					f->map[i][j] = 0;
					k++;
				}
				else if (f->buff[k] == 'N' || f->buff[k] == 'S'
					|| f->buff[k] == 'E' || f->buff[k] == 'W')
				{
					if (f->dir == '\0')
					{
						f->map[i][j] = 0;
						f->init[0] = i;
						f->init[1] = j;
						f->dir = f->buff[k];
					}
					else
						return (f->rtn = -1);
					k++;
				}
				j++;
			}
			k++;
			i++;
		}
	}
	return (0);
}
/*
**	ft_read_src_file:
**	devuelve 0 por default y -1 en error.
*/
int	ft_read_src_file(t_file *f)
{
	if (!f->w && !f->h) // TODO :COMPROBAR POR ARCHIVO
	{
		if ((ft_handle_resolution(f)) == -1 || f->w < 200
			|| f->w > 1920 || f->h < 200 || f->h > 1080)
			ft_handle_error("Res. ERROR while reading file. Bitch...\n");
	}
	else if (!f->texture[0] || !f->texture[1]
		|| !f->texture[2] || !f->texture[3])
	{
		if ((ft_handle_textures(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	else if (f->sprite == 0)
	{
		if ((ft_handle_spritex(f)) == -1)
			ft_handle_error("Text. ERROR while reading file. Nerd...\n");
	}
	else if (f->cf[0] == -1 || f->cf[1] == -1 || f->cf[2] == -1)
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
