/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_topdown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:21:19 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 13:48:22 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	put_box(mlx_texture_t *text, int x, int y, size_t color)
{
	int		scale;
	int		i;
	int		j;

	scale = SCALE;
	x -= scale;
	y -= scale;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			if (x + i < MINI_WIDTH && y + j < MINI_HEIGHT \
&& ((i != scale - 1 && j != scale - 1) || color == 0xFFFFFF))
				ft_texture(text, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	put_map(t_game *game)
{
	t_tile	**map;
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	x = game->minimap.x;
	y = game->minimap.y;
	map = game->map.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j].type != END)
		{
			if (map[i][j].type == WALL)
				put_box(game->game_t, map[i][j].x + x, map[i][j].y + y, 0xAAAAAA);
			else if (map[i][j].type == PATH)
				put_box(game->game_t, map[i][j].x + x, map[i][j].y + y, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
