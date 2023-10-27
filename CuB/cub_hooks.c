/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:37:07 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/26 16:01:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook_cub(t_main *game, int keycode)
{
	if (keycode == KEY_W)
		game->character.walk_dir = -1;
	else if (keycode == KEY_S)
		game->character.walk_dir = 1;
	else if (keycode == KEY_D)
		game->character.turn_dir = 1;
	else if (keycode == KEY_A)
		game->character.turn_dir = -1;
	else if (keycode == RIGHT_ARR)
		game->character.rots_dir = 1;
	else if (keycode == LEFT_ARR)
		game->character.rots_dir = -1;
	if (keycode == ESC)
		free_memory(game);
	return (0);
}

int	key_release(t_main *game, int keycode)
{
	if (keycode == KEY_W)
	{
		printf("keycode: %d\n", keycode);
		game->character.walk_dir = 0;
	}
	else if (keycode == KEY_S)
		game->character.walk_dir = 0;
	else if (keycode == KEY_D)
		game->character.turn_dir = 0;
	else if (keycode == KEY_A)
		game->character.turn_dir = 0;
	else if (keycode == RIGHT_ARR)
		game->character.rots_dir = 0;
	else if (keycode == LEFT_ARR)
		game->character.rots_dir = 0;
	return (0);
}