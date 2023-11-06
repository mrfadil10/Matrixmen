/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:53:28 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/06 17:04:08 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parse_map
{
	int	j;
	int	k;
}	t_parse_map;

static bool	is_endof_line(char *str)
{
	if (ft_strncmp(str, " \n", 2) == 0)
		return (true);
	return (false);
}

int	init_map_helper(t_main *game, t_init_map *struc)
{
	struc->iter.i = 0;
	game->parsing.lowest_indent = struc->lowest_indent;
	game->map.width = struc->width;
	game->map.height = struc->height;
	close(game->map.file.fd);
	if (check_is_open(game, game->map.file.path, &game->map.file.fd))
		return (1);
	while (struc->iter.i < game->parsing.lines_before_map + 1)
	{
		free(get_next_line(game->map.file.fd));
		struc->iter.i++;
	}
	game->map.array = (int **)malloc(sizeof(int *) * game->map.height);
	if (!game->map.array)
		return (set_err_msg(game, "\e[0;31mError: malloc"));
	game->parsing.map_is_init = true;
	return (0);
}

void	init_map_norm(t_init_map *struc)
{
	struc->iter.i = 0;
	while (struc->quick_line[struc->iter.i] && struc->quick_line[struc->iter.i] == ' ')
		struc->iter.i++;
	struc->iter.j = struc->iter.i;
	while (struc->quick_line[struc->iter.j]
		&& !is_endof_line(&struc->quick_line[struc->iter.j])
		&& struc->quick_line[struc->iter.j] != '\n')
		struc->iter.j++;
	if (struc->iter.j - struc->iter.i > struc->width)
		struc->width = struc->iter.j - struc->iter.i;
	if (struc->lowest_indent == -1)
		struc->lowest_indent = struc->iter.i;
	else if (struc->iter.i < struc->lowest_indent)
		struc->lowest_indent = struc->iter.i;
}

int	initialize_map(t_main *game)
{
	t_init_map	struc;

	ft_bzero(&struc, sizeof(t_init_map));
	struc.lowest_indent = -1;
	while (1)
	{
		struc.quick_line = get_next_line(game->map.file.fd);
		struc.height++;
		if (!struc.quick_line)
			break ;
		if (is_line_empty(struc.quick_line))
		{
			free(struc.quick_line);
			continue ;
		}
		init_map_norm(&struc);
		free(struc.quick_line);
	}
	return (init_map_helper(game, &struc));
}

static void	map_setting_helper(t_main *game, float degre, int i, int j)
{
	game->character.position.x = j * SIZEOF_TILE + SIZEOF_TILE / 2;
	game->character.position.y = i * SIZEOF_TILE + SIZEOF_TILE / 2; // to check
	game->character.width = 10;
	game->character.height = 32;
	game->character.mov_speed = 250;
	game->character.rots_speed = game->consts.rotation_speed; // to check
	game->character.angle = degre;
	game->map.array[i][j] = PLAYER;
}

static int	map_parsing_helper(t_main *game, t_parse_map *struc, char *line, int i)
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
		return (set_err_msg(game, "\e[0;31mError: Invalid character"));
	struc->k++;// to check
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
	game->map.array[i] = (int *)malloc(sizeof(int) * game->map.width);
	if (!game->map.array[i])
		return (set_err_msg(game, "\e[0;31mError: malloc"));
	struc.j = -1;
	struc.k = game->parsing.lowest_indent;
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
