/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:13:32 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/29 00:29:00 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parse_color
{
	char 		*trim;
	char		*join;
	char		*temp;
	char		**rgb;
	t_iter		iter;
}	t_parse_color;

static int	color_joiner(t_main *game, t_parse_color *str, char **line)
{
	str->join = ft_strdup("");
	if (!str->join)
		return (error_setter(game, "error malloc"));
	str->iter.i = 0;
	while (line[str->iter.i])
	{
		if (str->iter.i == 0)
			continue ;
		else
		{
			str->temp = str->join;
			str->join = ft_strjoin(str->join, line[str->iter.i]);
			free(str->temp);
		}
		str->iter.i++;
	}
	if (ft_occurences_counting(str->join, ',') != 2)
		return (error_setter(game, "Error: Invalid color"));
	str->rgb = ft_split(str->join, ",");
	free(str->join);
	if (!str->rgb)
		return (error_setter(game, "error malloc"));
	return (0);
}

static int	color_helper(t_main *game, t_parse_color *str)
{
	str->iter.i = 0;
	while (str->rgb[str->iter.i])
		str->iter.i++;
	if (str->iter.i != 3)
		return (error_setter(game, "Error: Invalid color"));
	str->iter.i = 0;
	while (str->rgb[str->iter.i])
	{
		str->trim = ft_strtrim(str->rgb[str->iter.i], " \t");
		if (!str->trim)
			return (error_setter(game, "error malloc"), free_dbl_ptr((void **)str->rgb));
		str->temp = str->rgb[str->iter.i];
		str->rgb[str->iter.i] = str->trim;
		free(str->temp);
		str->iter.j = 0;
		while (str->rgb[str->iter.i][str->iter.j])
		{
			if (!ft_isdigit(str->rgb[str->iter.i][str->iter.j]))
				return (error_setter(game, "Error: Invalid color"), free_dbl_ptr((void **)str->rgb));
			str->iter.j++;
		}
		return (0);
	}
}

int	parse_colors(t_main *game, t_color *rgb, char **arr, bool *is_colored)
{
	t_parse_color	str;

	if (*is_colored == true)
		return (error_setter(game, "Error: Duplicate identifier"));
	if (color_joiner(game, &str, arr))
		return (1);
	if (color_helper(game, &str))
		return (1);
	rgb->r = ft_atoi(str.rgb[0]);
	rgb->g = ft_atoi(str.rgb[1]);
	rgb->b = ft_atoi(str.rgb[2]);
	free_dbl_ptr((void **)str.rgb);
	if ((rgb->r < 0 || rgb->r > 255) || (rgb->g < 0 || rgb->g > 255)
		|| (rgb->b < 0 || rgb->b > 255))
		return (error_setter(game, "Error: Invalid color range"));
	*is_colored = true;
	return (0);
}

int	parse_textures(t_main *game, char **dup, char **line, bool *is_tex)
{
	int	fd;

	if (*is_tex == false)
		return (error_setter(game, "Error: Duplicate identifier"));
	fd = -1;
	while (line[++fd])
		;
	if (fd != 2)
		return (error_setter(game, "Error: Texture unknown error"));
	if (check_is_open(game, line[1], &fd))
		return (1);
	close(fd);
	*dup = ft_strdup(line[1]);
	*is_tex = true;
	return (0);
}

int	identify_file_lines(t_main *game, char **arr)
{
	if (ft_strncmp(arr[0], "NO", 3) == 0)
		return (parse_texture(game, &game->assets.north, arr, &game->parsing.no));
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
		return (parse_texture(game, &game->assets.south, arr, &game->parsing.so));
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
		return (parse_texture(game, &game->assets.east, arr, &game->parsing.ea));
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
		return (parse_texture(game, &game->assets.west, arr, &game->parsing.we));
	else if (ft_strncmp(arr[0], "F", 2) == 0)
		return (parse_colors(game, &game->assets.floor, arr, &game->parsing.floor));
	else if (ft_strncmp(arr[0], "C", 2) == 0)
		return (parse_colors(game, &game->assets.ceiling, arr, &game->parsing.ceiling));
	return (error_setter(game, "Error: Invalid identifier"));
}


int	parse_lineof_file(t_main *game, char *line)
{
	char	**split;

	if (game->parsing.map)
		return (map_parsing(game, line));
	line[ft_strlen(line) - 1] = 0;
	split = ft_split(line, " \t\n");
	if (!split)
		return (error_setter(game, "error malloc"));
	if (identify_file_lines(game, split))
		return (free_dbl_ptr((void **)split), 1);
	free_dbl_ptr((void **)split);
	return (0);
}