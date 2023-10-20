/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:23:50 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/20 23:54:50 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_movement(t_main *game)
{
	float	speed_mov;
	float	speed_cos;
	float	speed_sin;
	t_axes	diff;

	diff.x = 0;
	diff.y = 0;
	speed_mov = game->character.mov_speed * game->delta;
	speed_cos = speed_mov * cos(game->character.angle);
	speed_sin = speed_mov * sin(game->character.angle);
}