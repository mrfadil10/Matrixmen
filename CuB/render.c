/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:29:31 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/31 17:07:53 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct timespec s_time;

unsigned long long time_now()
{
	s_time	time;

	clock_gettime(CLOCK_MONOTONIC, &time);
	return (time.tv_sec * 1000 + time.tv_nsec / 1000000);
}

void	update_frame(t_main *game)
{
	static float	last_ticks = 0.0; // mybe just 0

	if (last_ticks < 0.5)
		last_ticks = (float)time_now();
	while ((float)time_now() - (last_ticks + game->consts.fps) < 0)
		;
	game->delta = (float)(time_now() - last_ticks) / 1000.0f;
	last_ticks = (float)time_now();
	moving_character(game);
	raycasting(game);
}

int	rendering_cub(t_main *game)
{
	static unsigned int	frames = 0;
	static unsigned int	fps = FPS;
	clock_t				elapse_tick;

	game->frame.ref = mlx_new_image(game->mlx, game->window.width, game->window.height);
	game->frame.addr = mlx_get_data_addr(game->frame.ref, &game->frame.bpp, &game->frame.line_lnt, &game->frame.endian);
	frames++;
	elapse_tick = clock() - game->time_to_start;
	if (game->time_to_start >= CLOCKS_PER_SEC)
	{
		fps = frames;
		game->time_to_start = clock();
		frames = 0;
	}
	puts("rendering");
	update_frame(game);
	mlx_put_image_to_window(game->mlx, game->window.reference, game->frame.ref, 0, 0);
	mlx_destroy_image(game->mlx, game->frame.ref);
	return (0);
}