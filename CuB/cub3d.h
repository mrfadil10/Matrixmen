/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:49:49 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/23 22:48:04 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include <mlx.h>
# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define FPS 40
# define SIZEOF_TILE 64
# define CHAR_SCALE 3
# define CHAR_WIDTH 10
# define CHAR_HEIGHT 32
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
	RIGHT_ARR = 1,
	LEFT_ARR = 2,
};

enum
{
	TXT_NO = 0,
	TXT_SO,
	TXT_EA,
	TXT_WE,
};

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_DESTROY = 17,
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
} t_file;

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
	bool	map;
	bool	buffer;
}	t_allocate;

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_parsing
{
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
	bool	floor;
}	t_parsing;

typedef struct s_error
{
	int		message;
	char	*code;
}	t_error;

typedef struct s_consts
{
	int		ray_nb;
	float	fps;
	float	tau;
	float	scale;
	float	mid_width;
	float	mid_height;
	
}	t_consts;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_assets
{
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
	int			width;
	int			height;
	float		angle;
	float		mov_speed;
	float		rots_speed;
	int			rots_dir;
	int			walk_dir;
	int			turn_dir;
	t_axes		position;
	t_axes		map_pos;
}	t_character;

typedef struct s_rays
{
	int			hit_content;
	bool		vertical_hit;
	float		angle;
	float		cos_x;
	float		sin_x;
	float		depth;
	float		proj_height;
	float		vert_depth;
	float		horz_depth;
	float		content_x;
	float		content_y;
	t_axes		proj_pt;
	t_axes		vert_pt;
	t_axes		horz_pt;
}	t_rays;

typedef struct s_main
{
	void		*mlx;
	bool		paused;
	bool		freeze;
	bool		over;
	float		delta;
	t_window	window;
	t_map		map;
	t_parsing	parsing;
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
int		set_cub_error(t_main *game, char *message);
int		init_cub3d(t_main *game);
int		free_memory(t_main *game);
int		key_hook_cub(t_main *game, int keycode);
int		key_release(t_main *game, int keycode);
void	check_collision(t_main *game, float δx, float δy);
int		moving_character(t_main *game);
bool	check_is_wall(int c);

#endif
