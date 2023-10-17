/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:49:49 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/17 19:40:26 by mfadil           ###   ########.fr       */
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
	float	scale;
	float	mid_width;
	float	mid_height;
}	t_consts;

typedef struct s_main
{
	void		*mlx;
	bool		paused;
	bool		freeze;
	bool		over;
	t_window	window;
	t_map		map;
	t_parsing	parsing;
	t_allocate	allocs;
	t_consts	consts;
}	t_main;

int	free_dbl_int(int **arr, size_t size);

#endif
