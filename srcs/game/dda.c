/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:51:38 by knakto            #+#    #+#             */
/*   Updated: 2025/06/16 02:06:42 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawline.h"
#include "game.h"
#include "map.h"

void	dda_map(t_game *game)
{
	t_player	player;
	t_tile		**map;
	int			i;
	int			j;
	int			k;
	int			p;

	player = game->player;
	map = game->map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].type != END)
		{
			if (map[i][j].type == WALL)
			{
				k = 0;
				while (k < SCALE)
				{
					p = 0;
					while (p < SCALE)
						ft_texture(game->game_t, map[i][j].x - p++, map[i][j].y - k, 0xAAAAAA);
					k++;
				}
			}
			k = 0;
			while (k < SCALE)
			{
				ft_texture(game->game_t, map[i][j].x - k, map[i][j].y, 0xFFFFFF);
				ft_texture(game->game_t, map[i][j].x, map[i][j].y - k, 0xFFFFFF);
				ft_texture(game->game_t, map[i][j].x - k, map[i][j].y - SCALE, 0xFFFFFF);
				ft_texture(game->game_t, map[i][j].x - SCALE, map[i][j].y - k, 0xFFFFFF);
				k++;
			}
			// printf("block: %d, %d\n%d,%d - %d,%d\n|            |\n%d,%d - %d,%d\n\n\n", j , i, map[i][j].x - SCALE, map[i][j].y - SCALE,
		 //  map[i][j].x, map[i][j].y - SCALE, map[i][j].x - SCALE, map[i][j].y, map[i][j].x, map[i][j].y);
			j++;
		}
		i++;
	}
	ft_texture(game->game_t, player.x, player.y, 0xFF0000);
}

void	ray_player(t_game *game)
{
	// int			i;
	float			j;
	t_tile		**map;
	t_player	player;
	// float		b;
	float		t;
	// float		l;
	// float		r;

	// i = 0;
	j = 0;
	player = game->player;
	map = game->map.map;
	// b = 0;
	t = 0;
	// l = 0;
	// r = 0;
	while (player.y - j > 0)
	{
		ft_texture(game->game_t, player.x, player.y - j, 0xFF0000);
		j += 0.1;
		if ((int)(player.y - j) % 10 == 0)
		{
			t = j;
			break ;
		}
			// if (map[(int)((player.y - (j + 1)) / SCALE)][(int)(player.x / SCALE)].type == WALL)
			// i++;
	}
	j = -1;
	while (player.y - (t + (SCALE * ++j)) > 0)
	{
		if (map[(int)((player.y - (t + 1 + (SCALE * j))) / SCALE)][(int)(player.x / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000, player.x, player.y, 0}, (t_point){0xFF0000, player.x, (player.y - (t + (SCALE * j))), 0});
			break ;
		}
	}

	// j = 0;
	// while (player.x - j > 0)
	// {
	// 	ft_texture(game->game_t, player.x- j, player.y, 0xFF0000);
	// 	j += 0.1;
	// 	if ((int)(player.x - j) % 10 == 0)
	// 		if (map[(int)(player.y / SCALE)][(int)((player.x - (j + 1)) / SCALE)].type == WALL)
	// 			break ;
	// 		// i++;
	// }
}

void	dda(t_game *game)
{
	dda_map(game);
	ray_player(game);
}
