/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:24:52 by mfadil            #+#    #+#             */
/*   Updated: 2023/11/09 23:27:27 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_endof_line(char *str)
{
	if (ft_strncmp(str, " \n", 2) == 0)
		return (true);
	return (false);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}
