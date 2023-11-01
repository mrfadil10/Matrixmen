/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:47:53 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/31 23:00:13 by mfadil           ###   ########.fr       */
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

void	cub_initialize(t_main *game, char *filename)
{
	game->window.width = WIN_WIDTH;
	game->window.height = WIN_HEIGHT;
	game->map.file.path = filename;
	game->parsing.map = false;
	game->parsing.map_is_init = false;
	game->parsing.no = false;
	game->parsing.so = false;
	game->parsing.ea = false;
	game->parsing.we = false;
	game->parsing.floor = false;
	game->parsing.ceiling = false;
	game->paused = false;
	game->freeze = false;
	game->rays = (t_rays *)malloc(sizeof(t_rays) * game->consts.ray_nb);
	if (!game->rays)
		error_exit(game, "Malloc failed");
}

void	init_constants(t_main *game)
{
	game->consts.fps = 1000 / FPS;
	game->consts.tau = 2 * M_PI;
	game->consts.mid_width = WIN_WIDTH / 2;
	game->consts.mid_height = WIN_HEIGHT / 2;
	game->consts.field_of_view = 60 * (M_PI / 180);
	game->consts.half_fov = game->consts.field_of_view / 2;
	game->consts.screen_distance = WIN_WIDTH / 2 / tan(game->consts.half_fov);
	game->consts.ray_nb = WIN_WIDTH;
	game->consts.half_ray_nb = game->consts.ray_nb / 2;
	game->consts.scale = WIN_WIDTH / game->consts.ray_nb;
	game->consts.angle_delta = game->consts.field_of_view / game->consts.ray_nb;
	game->consts.rotation_speed = 90 * (M_PI / 180);
}

int	main(int ac, char **av)
{
	t_main	game;

	ft_bzero(&game, sizeof(t_main));
	if (ac != 2)
		error_exit(&game, "\tUsage:\t./cub3D [filename].cub");
	init_constants(&game);
	if (ft_parser(&game, av[1]))
		error_exit(&game, game.error.message);
	game.mlx = mlx_init();
	game.window.reference = mlx_new_window(game.mlx, game.window.width, game.window.height, "cub3D");
	if (init_cub3d(&game))
		error_exit(&game, game.error.message);
	srand((unsigned int) time(NULL));
	game.time_to_start = clock();
	mlx_hook(game.window.reference, ON_DESTROY, 0L, free_memory, &game);
	mlx_hook(game.window.reference, ON_KEYDOWN, 0L, key_hook_cub, &game);
	mlx_hook(game.window.reference, ON_KEYUP, 0L, key_release, &game);
	mlx_loop_hook(game.mlx, rendering_cub, &game);
	mlx_loop(game.mlx);
}