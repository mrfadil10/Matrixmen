/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:11:26 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/06 17:04:08 by mfadil           ###   ########.fr       */
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

int	ft_check_occurs(t_main *game)
{
	int	i;
	int	occurs;

	i = -1;
	occurs = 0;
	while (++i < game->map.height)
		occurs += ft_int_occurences_counting(game->map.array[i], PLAYER,
				game->map.width);
	if (!occurs)
		return (set_err_msg(game, "\e[0;31mError: No player"));
	else if (occurs > 1)
		return (set_err_msg(game, "\e[0;31mError: Too many players"));
	return (0);
}

int	check_extension(t_main *game)
{
	int		count;
	char	**extension;

	count = ft_occurences_counting(game->map.file.path, '.');
	if (!count)
		return (set_err_msg(game, "\e[0;33mInvalid file"));
	if (!(count == 2 && game->map.file.path[0] == '.') && count > 1)
		return (set_err_msg(game, "\e[0;33mInvalid file"));
	extension = ft_split(game->map.file.path, ".");
	if (!extension)
		return (set_err_msg(game, "\e[0;31mError malloc"));
	count = 0;
	while (extension[count])
		count++;
	if (ft_strncmp(extension[count - 1], "cub", 4))
		return (free_dbl_ptr((void **)extension) + set_err_msg(game,
				"\e[0;33mInvalid file"));
	free_dbl_ptr((void **)extension);
	return (0);
}

bool	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}

int	check_map(t_main *game, char *line)
{
	static unsigned int	line_before_map = 0;

	if (game->parsing.no && game->parsing.so
		&& game->parsing.ea && game->parsing.we
		&& game->parsing.floor && game->parsing.ceiling && !game->parsing.map
		&& !is_line_empty(line))
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
	char	*line;

	while (1)
	{
		line = get_next_line(game->map.file.fd);
		printf("-->%s\n", line);
		if (!line)
			break ;
		if (is_line_empty(line))
		{
			if (game->parsing.map_is_init)
				return (free_cub3d(line),
					set_err_msg(game, "\e[0;33mEmpty line in map"));
			check_map(game, line);
			free_cub3d(line);
			continue ;
		}
		check_map(game, line);
		if (parse_lineof_file(game, line))
			return (free_cub3d(line), 1);
		free(line);
	}
	return (0);
}
