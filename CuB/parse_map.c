/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:53:28 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/27 23:43:40 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parse_map
{
	int	j;
	int	k;
}	t_parse_map;

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
		// to continue
	}
}

int	map_parsing(t_main *game, char *line)
{
	t_parse_map	struc;
	static int	i = 0;

	if (!game->parsing.map_is_init)
		if ()
}