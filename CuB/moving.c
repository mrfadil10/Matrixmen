/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:23:50 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/21 16:35:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_is_wall(int c)
{
	return (c == 1);
}

bool	has_wall_at(t_main *game, float x, float y)
{
	if (x < 0 || y < 0 || x < game->map.width * SIZEOF_TILE
		|| y < game->map.height * SIZEOF_TILE)
		return (check_is_wall(game->map.array[(int)(y / SIZEOF_TILE)]
				[(int)(x / SIZEOF_TILE)]));
}

int	moving_character(t_main *game)
{
	float	speed_mov;
	float	cos_vitesse;
	float	sin_vitesse;
	t_axes	diff;

	diff.x = 0;
	diff.y = 0;
	speed_mov = game->character.mov_speed * game->delta;
	cos_vitesse = speed_mov * cos(game->character.angle);
	sin_vitesse = speed_mov * sin(game->character.angle);
	diff.x += game->character.walk_dir * (-cos_vitesse);
	diff.x += game->character.turn_dir * (-sin_vitesse);
	diff.y += game->character.turn_dir * (cos_vitesse);
	diff.y += game->character.walk_dir * (-sin_vitesse);
	check_collision(game, diff.x, diff.y);
	game->character.angle += (game->character.rots_dir * game->character.rots_dir) *
		game->character.rots_dir;
}

void	check_collision(t_main *game, float δx, float δy)
{
	if (!has_wall_at(game, game->character.position.x + δx * CHAR_SCALE,
			game->character.position.y))
		game->character.position.x += δx;
	if (!has_wall_at(game, game->character.position.x,
			game->character.position.y + δy * CHAR_SCALE))
		game->character.position.y += δy;
	game->character.angle = fmod(game->character.angle, game->consts.tau);
	return (0);
}
