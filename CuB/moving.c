/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:23:50 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/09 23:19:44 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizon_steps(t_main *game, t_axes *distance, float *depth, int i)
{
	if (game->rays[i].sin_x > 0)
	{
		distance->y = SIZEOF_TILE;
		game->rays[i].horz_pt.y = (game->character.map_pos.y + 1) * SIZEOF_TILE;
	}
	else
	{
		distance->y = -SIZEOF_TILE;
		game->rays[i].horz_pt.y = game->character.map_pos.y
			* SIZEOF_TILE - 0.0001;
	}
	game->rays[i].horz_depth = game->rays[i].horz_pt.y
		- game->character.position.y;
	game->rays[i].horz_depth /= game->rays[i].sin_x;
	game->rays[i].horz_pt.x = game->rays[i].horz_depth * game->rays[i].cos_x;
	game->rays[i].horz_pt.x += game->character.position.x;
	*depth = distance->y / game->rays[i].sin_x;
	distance->x = *depth * game->rays[i].cos_x;
}

int	check_is_wall(int c)
{
	if (c == 1)
		return (1);
	return (0);
}

int	has_wall_at(t_main *game, float x, float y)
{
	if (x < 0 || y < 0 || x > game->map.width * SIZEOF_TILE
		|| y > game->map.height * SIZEOF_TILE)
		return (1);
	return (check_is_wall(game->map.array[(int)(y / SIZEOF_TILE)]
		[(int)(x / SIZEOF_TILE)]));
}

void	handle_wall_and_angle(t_main *game, t_axes diff)
{
	if (!has_wall_at(game, game->character.position.x + diff.x * CHAR_SCALE,
			game->character.position.y))
		game->character.position.x += diff.x;
	if (!has_wall_at(game, game->character.position.x,
			game->character.position.y + diff.y * CHAR_SCALE))
		game->character.position.y += diff.y;
	game->character.angle += (game->character.rots_dir
			* game->character.rots_dir) * game->character.rots_dir;
	game->character.angle = fmod(game->character.angle, game->consts.tau);
}

int	moving_character(t_main *game)
{
	float	speed_mov;
	float	cos_vitesse;
	float	sin_vitesse;
	t_axes	diff;

	diff.x = 0;
	diff.y = 0;
	speed_mov = game->character.mov_speed * game->diff;
	cos_vitesse = speed_mov * cos(game->character.angle);
	sin_vitesse = speed_mov * sin(game->character.angle);
	diff.x += game->character.walk_dir * (-cos_vitesse);
	diff.x += game->character.turn_dir * (-sin_vitesse);
	diff.y += game->character.turn_dir * (cos_vitesse);
	diff.y += game->character.walk_dir * (-sin_vitesse);
	handle_wall_and_angle(game, diff);
	return (0);
}
