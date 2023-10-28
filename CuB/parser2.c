/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:11:26 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/29 00:46:45 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_occurences_counting(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == c)
			count++;
	return (count);
}

int	check_extension(t_main *game)
{
	int		i;
	char	*extension;

	i = ft_occurences_counting(game->map.file.path, '.');
	if (!i)
		return (error_setter(game, "Invalid file"));
	if (!(i == 2 && game->map.file.path[0] == '.') && i > 1)
		return (error_setter(game, "Invalid file"));
	extension = ft_split(game->map.file.path, ".");
	if (!extension)
		return (error_setter(game, "error malloc"));
	i = -1;
	while (extension[++i])
		;
	if (ft_strncmp(extension[i - 1], "cub", 4))
		return (free_dbl_ptr((void **)extension)
		+ error_setter(game, "Invalid file"));
	free_dbl_ptr((void **)extension);
	return (0);
}

bool	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while ((line[i] >= 9 && line[i] <= 13) || line[++i] == ' ')
		;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}

int	check_map(t_main *game, char *line)
{
	static unsigned int	line_before_map = 0;

	if (game->parsing.no && game->parsing.so && game->parsing.ea && game->parsing.we
		&& game->parsing.floor && game->parsing.ceiling && !game->parsing.map && !is_line_empty(line))
	{
		game->parsing.lines_before_map = line_before_map;
		game->parsing.map = true;
	}
	if (!game->parsing.map)
		line_before_map++;
	return (0);
}

int	parse_config(t_main *game)
{
	char *line;

	while (1)
	{
		line = get_next_line(game->map.file.fd);
		if (!line)
			break ;
		if (is_line_empty(line))
		{
			if (game->parsing.map_is_init)
				return (free_cub3d(line), error_setter(game, "Empty line in map"));
			check_map(game, line);
			free_cub3d(line);
			continue ;
		}
		check_map(game, line);
		if (parse_lineof_file(game, line))
			return (free_cub3d(line), 1);
		free_cub3d(line);
	}
	return (0);
}