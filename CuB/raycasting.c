/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:01 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/21 22:42:01 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_main *game)
{
	t_iter	iter;
	t_axes	distances;
	float	angle;
	float	depth;

	iter.i = -1;
	game->character.position.x = (int)(game->character.position.x / SIZEOF_TILE);
	game->character.position.y = (int)(game->character.position.y / SIZEOF_TILE);
	angle = game->character.angle - game->character.width + 0.0001;
	while (++iter.i < WIN_WIDTH)
	{
		game->c
	}
}