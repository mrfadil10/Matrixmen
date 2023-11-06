/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:48:25 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/05 16:17:11 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_setter(t_main *game, char *error)
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
			return (error_setter(game, "\e[0;33mPermission denied"));
		else if (errno == ENOENT)
			return (error_setter(game, "\e[0;33mNo such file or directory"));
		else if (errno == EISDIR)
			return (error_setter(game, "\e[0;31mIs a directory"));
		else
			return (error_setter(game, "\e[0;31mUnknown error"));
	}
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

int	ft_parser(t_main *game, char *filename)
{
	cub_initialize(game, filename);
	if (parsing_file(game))
		return (1);
	if (close(game->map.file.fd) == -1)
		return (error_setter(game, "\e[0;31mError: could not close file"));
	if (check_borders(game))
		return (1);
	if (ft_check_occurs(game))
		return (1);
	return (0);
}
