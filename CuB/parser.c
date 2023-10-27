/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:48:25 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/27 11:46:04 by mfadil           ###   ########.fr       */
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
}

void	ft_parser(t_main *game, char *filename)
{
	cub_initialize(game, filename);

}