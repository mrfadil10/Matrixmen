/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:32:19 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/09 23:19:35 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_cub_error(t_main *game, char *message)
{
	game->error.message = message;
	game->error.code = 1;
	return (1);
}

int	free_cub3d(void *ptr)
{
	ft_free(ptr);
	return (1);
}

int	free_dbl_int(int **arr, size_t size)
{
	int	i;

	i = 0;
	while ((size_t)i < size)
	{
		free_cub3d(arr[i]);
		i++;
	}
	free_cub3d(arr);
	return (1);
}

int	free_memory(t_main *game)
{
	if (game->allocs.map)
		free_dbl_int(game->map.array, game->window.height);
	exit (0);
}

int	free_dbl_ptr(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_cub3d(tab[i]);
		i++;
	}
	free_cub3d(tab);
	return (1);
}
