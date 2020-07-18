/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 17:19:22 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/18 18:36:32 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_handle_error(char *str)
{
	perror(str);
	exit(0);
}

void	ft_handle_error_aux(char *str, void *aux)
{
	if (aux)
		free(aux);
	perror(str);
	exit(0);
}

void	ft_handle_error_ptr(char *str, void ***aux)
{
	int i;

	i = -1;
	while (aux[++i] != NULL)
		free(aux[i]);
	free(aux);
	perror(str);
	exit(0);
}

void	ft_free(void ***ptr)
{
	int i;

	i = -1;
	while (ptr[++i] != NULL)
		free(ptr[i]);
	free(ptr);
}
