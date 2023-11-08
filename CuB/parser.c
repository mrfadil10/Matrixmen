/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:48:25 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/08 22:41:26 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_err_msg(t_main *game, char *error)
{
	game->error.message = error;
	game->error.code = 1;
	return (1);
}

int	check_is_open(t_main *game, char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		if (errno == EACCES)
			return (set_err_msg(game, "\e[1;33mPermission denied"));
		else if (errno == ENOENT)
			return (set_err_msg(game, "\e[1;33mNo such file or directory"));
		else if (errno == EISDIR)
			return (set_err_msg(game, "\e[1;31mIs a directory"));
		else
			return (set_err_msg(game, "\e[1;31mUnknown error"));
	}
	return (0);
}

int	parse_lineof_file(t_main *game, char *line)
{
	size_t		i;
	char		**split;

	i = 0;
	if (game->parsing.map)
		return (map_parsing(game, line));
	while (line[i])
		i++;
	line[i - 1] = 0;
	split = ft_split(line, " \t\n");
	if (!split)
		return (set_err_msg(game, "\e[1;31merror malloc"));
	printf("split[0] = %s\n", split[0]);
	if (identify_file_lines(game, split))
		return (free_dbl_ptr((void **)split), 1);
	free_dbl_ptr((void **)split);
	return (0);
}

int	parsing_file(t_main *game)
{
	if (check_is_open(game, game->map.file.path, &game->map.file.fd))
		return (1);
	if (check_extension(game))
		return (1);
	if (parse_config(game))
		return (1);
	return (0);
}

int	ft_parsing_cub(t_main *game, char *filename)
{
	cub_initialize(game, filename);
	if (parsing_file(game))
		return (1);
	if (close(game->map.file.fd) == -1)
		return (set_err_msg(game, "\e[1;31mError: could not close file"));
	if (check_borders(game))
		return (1);
	return (0);
}
