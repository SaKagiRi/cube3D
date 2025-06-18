/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:51:38 by knakto            #+#    #+#             */
/*   Updated: 2025/06/17 22:30:11 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawline.h"
#include "game.h"
#include "map.h"
#include "unistd.h"

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
						ft_texture(game->game_t, map[i][j].x - p++, map[i][j].y - k, 0xAAAAAAFF);
					k++;
				}
			}
			k = 0;
			while (k < SCALE)
			{
				ft_texture(game->game_t, map[i][j].x - k, map[i][j].y, 0xFFFFFFFF);
				ft_texture(game->game_t, map[i][j].x, map[i][j].y - k, 0xFFFFFFFF);
				ft_texture(game->game_t, map[i][j].x - k, map[i][j].y - SCALE, 0xFFFFFFFF);
				ft_texture(game->game_t, map[i][j].x - SCALE, map[i][j].y - k, 0xFFFFFFFF);
				k++;
			}
			// printf("block: %d, %d\n%d,%d - %d,%d\n|            |\n%d,%d - %d,%d\n\n\n", j , i, map[i][j].x - SCALE, map[i][j].y - SCALE,
		 //  map[i][j].x, map[i][j].y - SCALE, map[i][j].x - SCALE, map[i][j].y, map[i][j].x, map[i][j].y);
			j++;
		}
		i++;
	}
	ft_texture(game->game_t, player.x, player.y, 0xFF0000FF);
}

void	put_dda(t_game *game, t_player player, t_vec2 gap)
{
	t_vec2		ofset;
	float		rad;
	t_tile		**map;

	ofset.x = 0;
	ofset.y = 0;
	rad = (player.dir_x - 90) * PI / 180;
	map = game->map.map;
	while (player.y + (gap.y + (SCALE * ofset.y)) > 0 && player.y + (gap.y + (SCALE * ofset.y)) < game->map.row * SCALE \
&& player.x + (gap.x + (SCALE * ofset.x)) > 0 && player.x + (gap.x + (SCALE * ofset.x)) < game->map.col * SCALE)
	{
		if (map[(int)((player.y + (gap.y + 1 + (SCALE * ofset.y))) / SCALE)][(int)(player.x / SCALE)].type == WALL \
|| map[(int)(player.y / SCALE)][(int)((player.x + (gap.x + 1 + (SCALE * ofset.x))) / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000FF, player.x, player.y, 0}, (t_point){0xFF0000FF, (player.x + (gap.x + (SCALE * ofset.x))), (player.y + (gap.y + (SCALE * ofset.y))), 0});
			break ;
		}
		ofset.x += cos(rad);
		ofset.y += sin(rad);
	}
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
	//top--------------------------------------------------------------------------------------------------------------------------------------------
	// t = get_gap(game, player).y;
	j = -1;
	while (player.y - (t + (SCALE * ++j)) > 0)
	{
		if (map[(int)((player.y - (t + 1 + (SCALE * j))) / SCALE)][(int)(player.x / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000FF, player.x, player.y, 0}, (t_point){0xFF0000FF, player.x, (player.y - (t + (SCALE * j))), 0});
			break ;
		}
	}
	//bot--------------------------------------------------------------------------------------------------------------------------------------------
	j = 0;
	while (player.y + j < get_game()->map.row * SCALE)
	{
		ft_texture(game->game_t, player.x, player.y + j, 0xFF0000FF);
		if ((int)(player.y + j) % 10 == 0)
		{
			t = j;
			break ;
		}
		j += 0.1;
	}
	j = -1;
	while (player.y + (t + (SCALE * ++j)) < get_game()->map.row * SCALE)
	{
		if (map[(int)((player.y + (t + 1 + (SCALE * j))) / SCALE)][(int)(player.x / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000FF, player.x, player.y, 0}, (t_point){0xFF0000FF, player.x, (player.y + (t + (SCALE * j))), 0});
			break ;
		}
	}
	//left--------------------------------------------------------------------------------------------------------------------------------------------
	j = 0;
	while (player.x - j > 0)
	{
		ft_texture(game->game_t, player.x - j, player.y, 0xFF0000FF);
		if ((int)(player.x - j) % 10 == 0)
		{
			t = j;
			break ;
		}
		j += 0.1;
	}
	j = -1;
	while (player.x - (t + (SCALE * ++j)) > 0)
	{
		if (map[(int)(player.y / SCALE)][(int)((player.x - (t + 1 + (SCALE * j))) / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000FF, player.x, player.y, 0}, (t_point){0xFF0000FF, (player.x - (t + (SCALE * j))), player.y , 0});
			break ;
		}
	}
	//right--------------------------------------------------------------------------------------------------------------------------------------------
	j = 0;
	while (player.x + j < get_game()->map.col * SCALE)
	{
		ft_texture(game->game_t, player.x + j, player.y, 0xFF0000FF);
		if ((int)(player.x + j) % 10 == 0)
		{
			t = j;
			break ;
		}
		j += 0.1;
	}
	j = -1;
	while (player.x + (t + (SCALE * ++j)) < get_game()->map.col * SCALE)
	{
		if (map[(int)(player.y / SCALE)][(int)((player.x + (t + 1 + (SCALE * j))) / SCALE)].type == WALL)
		{
			drawline(game->game_t, (t_point){0xFF0000FF, player.x, player.y, 0}, (t_point){0xFF0000FF, (player.x + (t + (SCALE * j))), player.y , 0});
			break ;
		}
	}
}

void	get_fist_sqare(t_game *game, t_vec2 gap, t_player player)
{
	float	xi;
	float	dx;
	float	yi;
	float	dy;
	float	c1;
	float	c2;
	float	rad;

	xi = 0;
	c2 = 0;
	c1 = 0;
	rad = -(player.dir_x - 90) * PI / 180;
	xi = (SCALE - gap.y) * sin(rad);
	c1 = c1 / cos(rad);
	yi = (SCALE - gap.x) * cos(rad);
	c2 = c2 / sin(rad);
	// xi = (SCALE - gap.y) / tan(rad);
	dx = SCALE * sin(rad);
	// yi = (SCALE - gap.x) * tan(rad);
	dy  = SCALE * cos(rad);
	drawline(game->game_t, (t_point){0xFF000000, player.x, player.y, 0},\
 (t_point){0xFF000000, player.x + xi + dx, player.y + yi + dy, 0});
	printf("xi:%f, yi:%f\n", xi, yi);
	(void)xi;
	(void)yi;
	(void)game;
	(void)dx;
	(void)dy;
}

void	dda(t_game *game)
{
	// t_vec2	gap;

	dda_map(game);
	// gap = get_gap(game, game->player);
	// printf("gap: x:%f, y:%f\n", gap.x, gap.y);
	// get_fist_sqare(game, gap, game->player);
	// put_dda(game, game->player, gap);
	// ray_player(game);
}
