/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:14:40 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 23:18:12 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "drawline.h"
#include "game.h"
#include <math.h>

static bool	in_wall(float x, float y, t_player *temp, float rad)
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
		if (get_game()->map.map[(int)(y / scale)][(int)(x / scale)].type == WALL)
			return (false);
		return (true);
	}
	if (map[(int)y / scale][(int)(temp->x / scale)].type == WALL \
&& map[(int)(temp->y / scale)][(int)(x / scale)].type == WALL)
	{
		temp->x += cos(rad) * 3;
		temp->y -= sin(rad) * 3;
		return (false);
	}
	return (true);
}

static bool	use_walk(int key, float *x1, float *y1, float rad)
{
	if (key == 'w')
	{
		*x1 -= sin(rad) * get_game()->player_speed;
		*y1 += cos(rad) * get_game()->player_speed;
		return (true);
	}
	else if (key == 's')
	{
		*x1 += sin(rad) * get_game()->player_speed;
		*y1 -= cos(rad) * get_game()->player_speed;
		return (true);
	}
	return (false);
}

void	player_walk(mlx_t *mlx)
{
	float		rad;
	float		*x1;
	float		*y1;
	t_player	temp;
	bool		status;

	rad = (get_game()->player.dir - 90) * PI / 180.0;
	x1 = &get_game()->player.x;
	y1 = &get_game()->player.y;
	status = false;
	temp.x = *x1;
	temp.y = *y1;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		status = use_walk('w', x1, y1, rad);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		status = use_walk('s', x1, y1, rad);
	if (!in_wall(*x1, *y1, &temp, rad))
	{
		*x1 = temp.x;
		*y1 = temp.y;
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

