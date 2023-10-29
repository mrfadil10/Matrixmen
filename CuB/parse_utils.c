/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:08:45 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/30 00:56:50 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_a_border(int c)
{
	if (c == 0 || c == CHARACTER)
		return (true);
	return (false);
}

static int	map_component(t_main *game, int i, int j)
{
	printf("11111game->map.array =");
	if (is_a_border(game->map.array[i][j + 1]) && j + 1 < game->map.width && game->map.array[i][j] == -1)
		return (error_setter(game, ""));
	if (is_a_border(game->map.array[i][j]) && j + 1 < game->map.width && game->map.array[i][j + 1] == -1)
		return (error_setter(game, "Error: Invalid border"));
	if (is_a_border(game->map.array[i + 1][j]) && i + 1 < game->map.height && game->map.array[i][j] == -1)
		return (error_setter(game, "Error: Invalid border"));
	if (is_a_border(game->map.array[i][j]) && i + 1 < game->map.height && game->map.array[i + 1][j] == -1)
		return (error_setter(game, "Error: Invalid border"));
	return (0);
}

int	check_borders(t_main *game)
{
	t_iter	iter;

	iter.i = 0;
	while (iter.i < game->map.width)
	{
		printf("game->map.array = %d\n", game->map.array[0][iter.i]);
		if (is_a_border(game->map.array[0][iter.i]) ||
			is_a_border(game->map.array[game->map.height - 1][iter.i]))
			return (error_setter(game, "Error: Invalid border"));
		iter.i++;
	}
	iter.i = 0;
	while (iter.i < game->map.height)
	{
		if (is_a_border(game->map.array[iter.i][0]) ||
			is_a_border(game->map.array[iter.i][game->map.width - 1]))
			return (error_setter(game, "Error: Invalid border"));
		iter.i++;
	}
	iter.i = 0;
	while (iter.i < game->map.height)
	{
		iter.j = 0;
		while (iter.j < game->map.width)
		{
			if (map_component(game, iter.i, iter.j))
				return (1);
			iter.j++;
		}
		iter.i++;
	}
	return (0);
}
