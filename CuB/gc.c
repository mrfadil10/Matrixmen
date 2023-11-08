/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:48:41 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/08 12:40:31 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(int status);

t_garbage_collector	*get_garbage_collector(void)
{
	static t_garbage_collector	gc;

	return (&gc);
}

void	*ft_malloc(size_t size)
{
	void				*ptr;
	t_garbage_collector	*last;

	last = get_garbage_collector();
	while (last->next)
		last = last->next;
	last->next = malloc(sizeof(t_garbage_collector));
	if (!last->next)
	{
		write(2, "malloc error!\n", 14);
		ft_exit(1);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "malloc error!\n", 14);
		ft_exit(1);
	}
	last->next->ptr = ptr;
	last->next->isfreed = 0;
	last->next->next = NULL;
	return (ptr);
}

void	ft_free(void *ptr)
{
	t_garbage_collector	*node;

	if (!ptr)
		return ;
	node = get_garbage_collector();
	while (node)
	{
		if (node->ptr == ptr)
		{
			if (!node->isfreed)
			{
				free(ptr);
				node->isfreed = 1;
				return ;
			}
		}
		node = node->next;
	}
	free(ptr);
}

void	ft_exit(int status)
{
	int						i;
	t_garbage_collector		*prev;
	t_garbage_collector		*node;

	i = 0;
	node = get_garbage_collector();
	while (node)
	{
		if (node->isfreed == 0)
		{
			node->isfreed = 1;
			if (node->ptr)
			{
				free(node->ptr);
			}
		}
		prev = node;
		node = node->next;
		if (i > 0)
			free(prev);
		i = i + 1;
	}
	exit(status);
}

// minimize windows
// memory miximize