/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:47:53 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/17 21:55:37 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(t_main *game, char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (game->allocs.map)
		free_dbl_int(game->map.array, (size_t) game->window.height);
	exit (1);
}

void	initialize(t_main *game)
{
	game->consts.mid_width = 800;
	game->consts.mid_height = 450;
	game->consts.fps = 25;
	game->consts.ray_nb = 1600;
}

int	main(int ac, char **av)
{
	t_main	game;

	if (ac != 2)
		error_exit(&game, "\tUsage:\t./cub3D [filename].cub");
	initialize(&game);
	// parsing
	game.mlx = mlx_init();
	game.window.reference = mlx_new_window(game.mlx, game.window.width, game.window.height, "cub3D");
}