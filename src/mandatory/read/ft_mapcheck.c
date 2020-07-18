/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:53:17 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 19:00:49 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int		ft_map_check(int row, int col, t_file *f)
{
	int ok;

	if (row < 0 || col < 0 || row >= f->nfil || col >= f->ncolmax ||
		f->map[row][col] == 4)
		return (-1);
	else if (f->map[row][col] == 3 || f->map[row][col] == 1 ||
		f->map[row][col] == 2)
		return (0);
	if (f->map[row][col] == 2)
		f->map[row][col] = 2;
	else
		f->map[row][col] = 3;
	ok = ft_map_check(row, col - 1, f);
	ok = ok == 0 ? ft_map_check(row, col + 1, f) : ok;
	ok = ok == 0 ? ft_map_check(row - 1, col, f) : ok;
	ok = ok == 0 ? ft_map_check(row + 1, col, f) : ok;
	return (f->rtn = ok);
}
