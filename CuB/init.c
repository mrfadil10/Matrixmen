/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:26:15 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/19 21:48:08 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_main *game)
{
	t_iter	iter;

	game->texture[TXT_NO].ref = mlx_xpm_file_to_image(game->mlx, game->assets.north, &iter.i, &iter.j);
	if (!game->texture[TXT_NO].ref)
		return (set_cub_error(game, "Failed to get address of north xpm."));
	game->texture[TXT_SO].ref = mlx_xpm_file_to_image(game->mlx, game->assets.south, &iter.i, &iter.j);
	if (!game->texture[TXT_SO].ref)
		return (set_cub_error(game, "Failed to get address of south xpm."));
	game->texture[TXT_EA].ref = mlx_xpm_file_to_image(game->mlx, game->assets.east, &iter.i, &iter.j);
	if (!game->texture[TXT_EA].ref)
		return (set_cub_error(game, "Failed to get address of east xpm."));
	game->texture[TXT_WE].ref = mlx_xpm_file_to_image(game->mlx, game->assets.west, &iter.i, &iter.j);
	if (!game->texture[TXT_WE].ref)
		return (set_cub_error(game, "Failed to get address of west xpm."));
	return (1);
}



int	init_cub3d(t_main *game)
{
	if (init_textures(game))
		return (1);
	return (0);
}