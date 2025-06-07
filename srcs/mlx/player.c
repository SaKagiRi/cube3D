/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:14:40 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 12:57:53 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "drawline.h"
#include "game.h"
#include <math.h>

static bool	in_wall(float x, float y, t_player *temp)
{
	t_tile	**map;
	int		scale;

	scale = get_game()->scale;
	map = get_game()->map.map;
	if ((int)(x) == (int)(temp->x) && (int)(y) == (int)(temp->y))
		return (false);
	if ((int)(x / scale) == (int)(temp->x / scale) \
|| (int)(y / scale) == (int)(temp->y / scale))
	{
		if (map[(int)(y / scale)][(int)(x / scale)].type == WALL)
			return (false);
		return (true);
	}
	if (map[(int)y / scale][(int)(temp->x / scale)].type == WALL \
&& map[(int)(temp->y / scale)][(int)(x / scale)].type == WALL)
		return (true);
	return (true);
}

static bool	use_walk(int key, float *x1, float *y1, float rad)
{
	t_game	*game;

	game = get_game();
	if (key == 'w')
	{
		*x1 -= sin(rad) * game->player_speed;
		*y1 += cos(rad) * game->player_speed;
		return (true);
	}
	else if (key == 's')
	{
		*x1 += sin(rad) * game->player_speed;
		*y1 -= cos(rad) * game->player_speed;
		return (true);
	}
	return (false);
}

void	player_walk(mlx_t *mlx)
{
	t_player	*player;
	t_player	temp;
	float		rad;
	bool		status;

	player = &get_game()->player;
	rad = (player->dir - 90) * PI / 180;
	status = false;
	temp.x = player->x;
	temp.y = player->y;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		status = use_walk('w', &player->x, &player->y, rad);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		status = use_walk('s', &player->x, &player->y, rad);
	if (!in_wall(player->x, player->y, &temp))
	{
		player->x = temp.x;
		player->y = temp.y;
	}
	if (status)
		get_game()->on_change = 0;
}

void	put_player(mlx_texture_t *text, t_player player, size_t color)
{
	float		padding;
	t_point		front;
	t_point		left;
	t_point		right;
	float		redian;

	padding = get_game()->player_size;
	redian = player.dir * PI / 180;
	front.color = color;
	front.outcode = 0;
	front.px = player.x + padding * cos(redian);
	front.py = player.y + padding * sin(redian);
	left.color = color;
	left.outcode = 0;
	left.px = player.x + (padding / 2) * cos(redian - PI / 1.5);
	left.py = player.y + (padding / 2) * sin(redian - PI / 1.5);
	right.color = color;
	right.outcode = 0;
	right.px = player.x + (padding / 2) * cos(redian + PI / 1.5);
	right.py = player.y + (padding / 2) * sin(redian + PI / 1.5);
	bresenham(text, front, left);
	bresenham(text, front, right);
	bresenham(text, left, right);
	ft_texture(text, player.x, player.y, color);
}

