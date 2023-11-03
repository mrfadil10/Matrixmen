/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:01 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/03 22:42:43 by mfadil           ###   ########.fr       */
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
		game->rays[i].horz_pt.y = game->character.map_pos.y * SIZEOF_TILE - 0.0001;
	}
	game->rays[i].horz_depth = game->rays[i].horz_pt.y - game->character.position.y;
	game->rays[i].horz_depth /= game->rays[i].sin_x;
	game->rays[i].horz_pt.x = game->rays[i].horz_depth * game->rays[i].cos_x;
	game->rays[i].horz_pt.x += game->character.position.x;
	*depth = distance->y / game->rays[i].sin_x;
	distance->x = *depth * game->rays[i].cos_x;
}

void	vertical_steps(t_main *game, t_axes *distance, float *depth, int i)
{
	if (game->rays[i].cos_x > 0)
	{
		distance->x = SIZEOF_TILE;
		game->rays[i].vert_pt.x = (game->character.map_pos.x + 1) * SIZEOF_TILE;
	}
	else
	{
		distance->x = -SIZEOF_TILE;
		game->rays[i].vert_pt.x = game->character.map_pos.x * SIZEOF_TILE - 0.0001;
	}
	game->rays[i].vert_depth = game->rays[i].vert_pt.x - game->character.position.x;
	game->rays[i].vert_depth /= game->rays[i].cos_x;
	game->rays[i].vert_pt.y = game->rays[i].vert_depth * game->rays[i].sin_x;
	game->rays[i].vert_pt.y += game->character.position.y;
	*depth = distance->x / game->rays[i].cos_x;
	distance->y = *depth * game->rays[i].sin_x;
}

void	horizontal_inter(t_main *game, t_axes *distance, float depth, int i)
{
	int		j;
	t_iter	tile;

	j = 0;
	while (j < MAX_DEPTH)
	{
		tile.i = abs((int)(game->rays[i].horz_pt.y / SIZEOF_TILE));
		tile.j = abs((int)(game->rays[i].horz_pt.x / SIZEOF_TILE));
		if (tile.j >= game->map.width || tile.i >= game->map.height)
			break ;
		if (check_is_wall(game->map.array[tile.i][tile.j]))
		{
			game->rays[i].content_x = game->map.array[tile.i][tile.j];
			break ;
		}
		game->rays[i].horz_depth += depth;
		game->rays[i].horz_pt.x += distance->x;
		game->rays[i].horz_pt.y += distance->y;
		j++;
	}
}

void	vertical_inter(t_main *game, t_axes *distance, float depth, int i)
{
	int		j;
	t_iter	tile;

	j = 0;
	while (j < MAX_DEPTH)
	{
		tile.i = abs((int)(game->rays[i].vert_pt.y / SIZEOF_TILE));
		tile.j = abs((int)(game->rays[i].vert_pt.x / SIZEOF_TILE));
		if (tile.j >= game->map.width || tile.i >= game->map.height)
			break ;
		if (check_is_wall(game->map.array[tile.i][tile.j]))
		{
			game->rays[i].content_y = game->map.array[tile.i][tile.j];
			break ;
		}
		game->rays[i].vert_depth += depth;
		game->rays[i].vert_pt.x += distance->x;
		game->rays[i].vert_pt.y += distance->y;
		j++;
	}
}

void	intersection(t_main *game, int i)
{
	if (game->rays[i].vert_depth < game->rays[i].horz_depth)
	{
		game->rays[i].vert_pt.y = fmod(game->rays[i].vert_pt.y, SIZEOF_TILE);
		game->rays[i].depth = game->rays[i].vert_depth;
		game->rays[i].proj_pt = game->rays[i].vert_pt;
		game->rays[i].hit_content = game->rays[i].content_y;
		game->rays[i].vertical_hit = true;
	}
	else
	{
		game->rays[i].horz_pt.x = fmod(game->rays[i].horz_pt.x, SIZEOF_TILE);
		game->rays[i].depth = game->rays[i].horz_depth;
		game->rays[i].proj_pt = game->rays[i].horz_pt;
		game->rays[i].hit_content = game->rays[i].content_x;
		game->rays[i].vertical_hit = false;
	}
}

void	steps_and_intersection(t_main *game, int i)
{
	t_axes	distances;
	float	depth;
	horizon_steps(game, &distances, &depth, i);
	horizontal_inter(game, &distances, depth, i);
	vertical_steps(game, &distances, &depth, i);
	vertical_inter(game, &distances, depth, i);
	intersection(game, i);
}
void	raycasting(t_main *game)
{
	t_iter	iter;
	//t_axes	distances;
	float	angle;
	//float	depth;

	iter.i = 0;
	game->character.map_pos.x = (int)(game->character.position.x / SIZEOF_TILE);
	game->character.map_pos.y = (int)(game->character.position.y / SIZEOF_TILE);
	angle = game->character.angle - game->consts.half_fov + 0.0001;
	while (iter.i < WIN_WIDTH)
	{
		game->rays[iter.i].angle = angle;
		game->rays[iter.i].cos_x = cos(angle);
		game->rays[iter.i].sin_x = sin(angle);
		//horizon_steps(game, &distances, &depth, iter.i);
		//horizontal_inter(game, &distances, depth, iter.i);
		//vertical_steps(game, &distances, &depth, iter.i);
		//vertical_inter(game, &distances, depth, iter.i);
		//intersection(game, iter.i);
		steps_and_intersection(game, iter.i);
		drawing_walls(game, iter, angle);
		angle += game->consts.angle_delta;
		iter.i++;
	}
}
