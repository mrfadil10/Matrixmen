/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:48:25 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/29 17:30:22 by mfadil           ###   ########.fr       */
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
			return (error_setter(game, "Permission denied"));
		else if (errno == ENOENT)
			return (error_setter(game, "No such file or directory"));
		else
			return (error_setter(game, "Unknown error"));
		//else if (errno == EISDIR)
		//	return (error_setter(game, "Is a directory"));
	}
	return (0);
}

int	check_is_exist(t_main *game)
{
	return (check_is_open(game, game->map.file.path, &game->map.file.fd));
}

int	parsing_file(t_main *game)
{
	if (check_is_exist(game))
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
		return (error_setter(game, "Error: could not close file"));
	printf("parsing_file\n");
	printf("game->map.array = %d\n", game->map.array[0][0]);
	if (check_borders(game))
		return (1);
	if (ft_check_occurs(game))
		return (1);
	return (0);
}