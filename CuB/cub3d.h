/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:49:49 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/10 16:23:35 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include <mlx.h>
# include "./libft/libft.h"
# include "./Gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 500
# define FPS 60
# define SIZEOF_TILE 64
# define CHAR_SCALE 5
# define MAX_DEPTH 100

enum
{
	PLAYER = 99,
};

enum
{
	KEY_UP = 3,
	KEY_DOWN = 2,
	KEY_DESTROY = 17,
};

enum
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	ESC = 53,
};

enum
{
	RIGHT_ARR = 124,
	LEFT_ARR = 123,
};

enum
{
	TXT_NO = 0,
	TXT_SO,
	TXT_EA,
	TXT_WE,
};

typedef struct s_garbage_collector	t_garbage_collector;
struct s_garbage_collector
{
	void				*ptr;
	int					isfreed;
	t_garbage_collector	*next;
};

typedef struct s_iter
{
	int	i;
	int	j;
}	t_iter;

typedef struct s_axes
{
	float	x;
	float	y;
}	t_axes;

typedef struct s_file
{
	int		fd;
	char	*path;
}	t_file;

typedef struct s_img
{
	int		endian;
	int		line_lnt;
	int		bpp;
	char	*addr;
	void	*ref;
}	t_img;

typedef struct s_map
{
	int		width;
	int		height;
	int		**array;
	t_file	file;
}	t_map;

typedef struct s_window
{
	int		width;
	int		height;
	void	*reference;
}	t_window;

typedef struct s_allocate
{
	bool	buffer;
	bool	map;
}	t_allocate;

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_parsing
{
	int		lines_count;
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
	bool	floor;
	bool	map;
	bool	map_is_init;
	bool	ceiling;
	int		closest_dis;
}	t_parser;

typedef struct s_error
{
	int		message;
	char	*code;
}	t_error;

typedef struct s_consts
{
	int		ray_nb;
	float	field_of_view;
	float	half_fov;
	float	fps;
	float	tau;
	float	scale;
	float	mid_height;
	float	angle_delta;
	float	screen_distance;
	float	rotation_speed;
}	t_consts;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_assets
{
	t_rgb	floor;
	t_rgb	ceiling;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_assets;

typedef struct s_err
{
	int		code;
	char	*message;
}	t_err;

typedef struct s_character
{
	float		angle;
	float		mov_speed;
	float		rots_dir;
	int			walk_dir;
	int			turn_dir;
	t_axes		position;
	t_axes		map_pos;
}	t_character;

typedef struct s_rays
{
	bool		vertical_hit;
	float		angle;
	float		cos_x;
	float		sin_x;
	float		depth;
	float		proj_height;
	float		vert_depth;
	float		horz_depth;
	t_axes		proj_pt;
	t_axes		vert_pt;
	t_axes		horz_pt;
}	t_rays;

typedef struct s_draw_walls
{
	int			i;
	int			top_pixel;
	int			bot_pixel;
	float		depth;
}	t_draw_walls;

typedef struct s_init_map
{
	int		width;
	int		height;
	int		closest_dis;
	char	*quick_line;
	t_iter	iter;
}	t_init_map;

typedef struct s_main
{
	void		*mlx;
	float		diff;
	t_window	window;
	t_map		map;
	t_parser	parsing;
	t_allocate	allocs;
	t_consts	consts;
	t_img		frame;
	t_img		texture[4];
	t_assets	assets;
	t_err		error;
	clock_t		time_to_start;
	t_character	character;
	t_rays		*rays;
}	t_main;

int		free_dbl_int(int **arr, size_t size);
int		free_dbl_ptr(void **tab);
int		set_cub_error(t_main *game, char *message);
int		init_cub3d(t_main *game);
int		free_memory(t_main *game);
int		key_hook_cub(int keycode, t_main *game);
int		init_keys(int keycode, t_main *game);
void	check_collision(t_main *game, float dx, float dy);
int		moving_character(t_main *game);
int		check_is_wall(int c);
void	raycasting(t_main *game);
int		rendering_cub(t_main *game);
void	drawing_walls(t_main *game, t_iter iter, float ray_angle);
void	put_pixel(t_main *game, int color, float x, float y);

// parsing

int		parse_config(t_main *game);
void	cub_initialize(t_main *game, char *filename);
int		set_err_msg(t_main *game, char *error);
int		check_extension(t_main *game);
int		free_cub3d(void *ptr);
int		check_is_open(t_main *game, char *filename, int *fd);
int		ft_occurences_counting(char *str, char c);
int		ft_int_occurences_counting(int *str, int c, size_t size);
int		ft_check_occurs(t_main *game);
int		is_line_empty(char *line);
int		map_parsing(t_main *game, char *line);
int		parse_lineof_file(t_main *game, char *line);
int		check_borders(t_main *game);
int		ft_parsing_cub(t_main *game, char *filename);
int		identify_file_lines(t_main *game, char **arr);
int		create_rgb(t_rgb color);
int		ft_int_occurences_counting(int *str, int c, size_t size);
void	horizon_steps(t_main *game, t_axes *distance, float *depth, int i);
void	intersection(t_main *game, int i);
void	map_setting_helper(t_main *game, float degre, int i, int j);
bool	is_endof_line(char *str);
int		is_line_empty(char *line);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	ft_exit(int status);

#endif
