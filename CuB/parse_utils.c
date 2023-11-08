/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:08:45 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/08 22:41:45 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_a_border(int c)
{
	if (c == 0 || c == PLAYER)
		return (true);
	return (false);
}

int	ft_int_occurences_counting(int *str, int c, size_t size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((size_t)i < size)
		if (str[i++] == c)
			count++;
	return (count);
}

int	map_component(t_main *game, int i, int j)
{
	if (j + 1 < game->map.width && is_a_border(game->map.array[i][j + 1])
		&& game->map.array[i][j] == -1)
		return (set_err_msg(game, "\e[1;31mError: Invalid border"));
	if (j + 1 < game->map.width && is_a_border(game->map.array[i][j])
		&& game->map.array[i][j + 1] == -1)
		return (set_err_msg(game, "\e[1;31mError: Invalid border"));
	if (i + 1 < game->map.height && is_a_border(game->map.array[i + 1][j])
		&& game->map.array[i][j] == -1)
		return (set_err_msg(game, "\e[1;31mError: Invalid border"));
	if (i + 1 < game->map.height && is_a_border(game->map.array[i][j])
		&& game->map.array[i + 1][j] == -1)
		return (set_err_msg(game, "\e[1;31mError: Invalid border"));
	return (0);
}

int	check_map_components(t_main *game, t_iter iter)
{
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

int	check_borders(t_main *game)
{
	t_iter	iter;

	iter.i = 0;
	while (iter.i < game->map.width)
	{
		if (is_a_border(game->map.array[0][iter.i]) ||
			is_a_border(game->map.array[game->map.height - 1][iter.i]))
			return (set_err_msg(game, "\e[1;31mError: Invalid border"));
		iter.i++;
	}
	iter.i = 0;
	while (iter.i < game->map.height)
	{
		if (is_a_border(game->map.array[iter.i][0]) ||
			is_a_border(game->map.array[iter.i][game->map.width - 1]))
			return (set_err_msg(game, "\e[1;31mError: Invalid border"));
		iter.i++;
	}
	iter.i = 0;
	if (check_map_components(game, iter))
		return (1);
	if (ft_check_occurs(game))
		return (1);
	return (0);
}
