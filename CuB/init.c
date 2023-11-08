/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:26:15 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/08 16:17:09 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

int	load_textures(t_main *game)
{
	game->texture[TXT_NO].addr = mlx_get_data_addr(game->texture[TXT_NO].ref,
			&game->texture[TXT_NO].bpp, &game->texture[TXT_NO].line_lnt,
			&game->texture[TXT_NO].endian);
	if (!game->texture[TXT_NO].addr)
		return (set_err_msg(game, "\e[1;31mFailed to reach north xpm."));
	game->texture[TXT_SO].addr = mlx_get_data_addr(game->texture[TXT_SO].ref,
			&game->texture[TXT_SO].bpp, &game->texture[TXT_SO].line_lnt,
			&game->texture[TXT_SO].endian);
	if (!game->texture[TXT_SO].addr)
		return (set_err_msg(game, "\e[1;31mFailed to reach south xpm."));
	game->texture[TXT_EA].addr = mlx_get_data_addr(game->texture[TXT_EA].ref,
			&game->texture[TXT_EA].bpp, &game->texture[TXT_EA].line_lnt,
			&game->texture[TXT_EA].endian);
	if (!game->texture[TXT_EA].addr)
		return (set_err_msg(game, "\e[1;31mFailed to reach east xpm."));
	game->texture[TXT_WE].addr = mlx_get_data_addr(game->texture[TXT_WE].ref,
			&game->texture[TXT_WE].bpp, &game->texture[TXT_WE].line_lnt,
			&game->texture[TXT_WE].endian);
	if (!game->texture[TXT_WE].addr)
		return (set_err_msg(game, "\e[1;31mFailed to reach west xpm."));
	return (0);
}

int	init_textures(t_main *game)
{
	t_iter	iter;

	game->texture[TXT_NO].ref = mlx_xpm_file_to_image(game->mlx,
			game->assets.north, &iter.i, &iter.j);
	if (!game->texture[TXT_NO].ref)
		return (set_cub_error(game, "\e[1;31mFailed to reach north xpm."));
	game->texture[TXT_SO].ref = mlx_xpm_file_to_image(game->mlx,
			game->assets.south, &iter.i, &iter.j);
	if (!game->texture[TXT_SO].ref)
		return (set_cub_error(game, "\e[1;31mFailed to reach south xpm."));
	game->texture[TXT_EA].ref = mlx_xpm_file_to_image(game->mlx,
			game->assets.east, &iter.i, &iter.j);
	if (!game->texture[TXT_EA].ref)
		return (set_cub_error(game, "\e[1;31mFailed to reach east xpm."));
	game->texture[TXT_WE].ref = mlx_xpm_file_to_image(game->mlx,
			game->assets.west, &iter.i, &iter.j);
	if (!game->texture[TXT_WE].ref)
		return (set_cub_error(game, "\e[1;31mFailed to reach west xpm."));
	load_textures(game);
	return (0);
}

int	init_cub3d(t_main *game)
{
	if (init_textures(game))
		return (1);
	return (0);
}
