/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:53:28 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/09 23:23:18 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parse_map
{
	int	j;
	int	k;
}	t_parse_map;

int	init_map_helper(t_main *game, t_init_map *struc)
{
	struc->iter.i = 0;
	game->parsing.closest_dis = struc->closest_dis;
	game->map.width = struc->width;
	game->map.height = struc->height;
	close(game->map.file.fd);
	if (check_is_open(game, game->map.file.path, &game->map.file.fd))
		return (1);
	while (struc->iter.i < game->parsing.lines_count + 1)
	{
		ft_free(get_next_line(game->map.file.fd));
		struc->iter.i++;
	}
	game->map.array = (int **)ft_malloc(sizeof(int *) * game->map.height);
	if (!game->map.array)
		return (set_err_msg(game, "\e[1;31mError: malloc"));
	game->parsing.map_is_init = true;
	return (0);
}

void	init_map_norm(t_init_map *struc)
{
	struc->iter.i = 0;
	while (struc->quick_line[struc->iter.i]
		&& struc->quick_line[struc->iter.i] == ' ')
		struc->iter.i++;
	struc->iter.j = struc->iter.i;
	while (struc->quick_line[struc->iter.j]
		&& !is_endof_line(&struc->quick_line[struc->iter.j])
		&& struc->quick_line[struc->iter.j] != '\n')
		struc->iter.j++;
	if (struc->iter.j - struc->iter.i > struc->width)
		struc->width = struc->iter.j - struc->iter.i;
	if (struc->closest_dis == -1)
		struc->closest_dis = struc->iter.i;
	else if (struc->iter.i < struc->closest_dis)
		struc->closest_dis = struc->iter.i;
}

int	initialize_map(t_main *game)
{
	t_init_map	struc;

	ft_bzero(&struc, sizeof(t_init_map));
	struc.closest_dis = -1;
	while (1)
	{
		struc.quick_line = get_next_line(game->map.file.fd);
		struc.height++;
		if (!struc.quick_line)
			break ;
		if (is_line_empty(struc.quick_line))
		{
			ft_free(struc.quick_line);
			continue ;
		}
		init_map_norm(&struc);
		ft_free(struc.quick_line);
	}
	return (init_map_helper(game, &struc));
}

static int	map_parsing_helper(t_main *game, t_parse_map *struc,
		char *line, int i)
{
	if (line[struc->k] == 'N')
		map_setting_helper(game, 3 * M_PI / 2, i, struc->j);
	else if (line[struc->k] == 'S')
		map_setting_helper(game, M_PI / 2, i, struc->j);
	else if (line[struc->k] == 'E')
		map_setting_helper(game, 2 * M_PI, i, struc->j);
	else if (line[struc->k] == 'W')
		map_setting_helper(game, M_PI, i, struc->j);
	else if (line[struc->k] >= '0' && line[struc->k] <= '5')
		game->map.array[i][struc->j] = line[struc->k] - '0';
	else if (line[struc->k] == ' ')
		game->map.array[i][struc->j] = -1;
	else
		return (set_err_msg(game, "\e[1;31mError: Invalid character"));
	struc->k++;
	return (0);
}

int	map_parsing(t_main *game, char *line)
{
	t_parse_map	struc;
	static int	i = 0;

	if (!game->parsing.map_is_init)
		if (initialize_map(game))
			return (1);
	if (i >= game->map.height + 1)
		return (set_err_msg(game, "\e[0;31mError: index out of range"));
	game->map.array[i] = (int *)ft_malloc(sizeof(int) * game->map.width);
	if (!game->map.array[i])
		return (set_err_msg(game, "\e[0;31mError: malloc"));
	struc.j = -1;
	struc.k = game->parsing.closest_dis;
	while (++struc.j < game->map.width)
	{
		if (line[struc.k] && line[struc.k] != '\n')
		{
			if (map_parsing_helper(game, &struc, line, i))
				return (1);
		}
		else
			game->map.array[i][struc.j] = -1;
	}
	i++;
	return (0);
}
