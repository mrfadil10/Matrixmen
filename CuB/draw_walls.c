/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:56:35 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/24 17:45:15 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_textcolor(t_main *game, int txt, t_iter text_off)
{
	int	ind;

	ind = (text_off.i * SIZEOF_TILE) + text_off.j;
	return (((unsigned int *) game->texture[txt].addr)[ind]);
}

void	put_stripe(t_main *game, t_iter text_off, t_iter iter, int i)
{
	unsigned int	text_color;

	if (game->rays[iter.i].vertical_hit)
	{
		if (game->rays[iter.i].horz_pt.x > game->character.position.x)
			text_color = get_textcolor(game, TXT_EA, text_off);
		else
			text_color = get_textcolor(game, TXT_WE, text_off);
	}
	else
	{
		if (game->rays[iter.i].vert_pt.y > game->character.position.y)
			text_color = get_textcolor(game, TXT_SO, text_off);
		else
			text_color = get_textcolor(game, TXT_NO, text_off);
	}
	put_pixel(game, text_color, iter.i * game->consts.scale, i);
}

void	drawing_stripe(t_main *game, t_iter iter, int top_wall, int wall_bottom)
{
	t_iter	text_offset;
	float	d;
	int		i;

	if (game->rays[iter.i].vertical_hit)
		text_offset.j = (int)game->rays[iter.i].vert_pt.y;
	else
		text_offset.j = (int)game->rays[iter.i].horz_pt.x;
	d = SIZEOF_TILE / game->rays[iter.i].depth;
	i = top_wall;
	while (i < wall_bottom)
	{
		text_offset.i = (i + (int)game->rays[iter.i].proj_height / 2
				- game->consts.mid_height) * d;

	}
}

int	create_rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

void	put_pixel(t_main *game, int color, float x, float y)
{
	t_img	*img;
	char	*dst;
	int		int_x;
	int		int_y;

	img = &game->frame;
	int_x = (int)round(x);
	int_y = (int)round(y);
	if (x < 0 || y < 0 || x > game->window.width || y > game->window.height)
		return ;
	dst = img->addr + (int_y * img->line_lnt + int_x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawing_walls(t_main *game, t_iter iter, float ray_angle)
{
	t_draw_walls	str;

	str.depth = game->rays[iter.i].depth * cos(game->character.angle - ray_angle);
	game->rays[iter.i].proj_height = (SIZEOF_TILE / str.depth) * game->consts.screen_distance;
	str.wall_top_pixel = game->consts.mid_height - (int) game->rays[iter.i].proj_height / 2;
	if (str.wall_top_pixel < 0)
		str.wall_top_pixel = 0;
	str.wall_bottom_pixel = game->consts.mid_height + (int) game->rays[iter.i].proj_height / 2;
	if (str.wall_bottom_pixel > WIN_HEIGHT)
		str.wall_bottom_pixel = WIN_HEIGHT;
	str.i = -1;
	while (++str.i < str.wall_top_pixel)
		put_pixel(game, create_rgb(game->assets.ceiling), iter.i * game->consts.scale, str.i);
	drawing_stripe(game, iter, str.wall_top_pixel, str.wall_bottom_pixel);
	str.i = str.wall_bottom_pixel - 1;
	while (++str.i < WIN_HEIGHT)
		put_pixel(game, create_rgb(game->assets.floor), iter.i * game->consts.scale, str.i);
}
