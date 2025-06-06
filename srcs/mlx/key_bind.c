/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:34:39 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 19:07:15 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include <math.h>

bool	in_wall(float x, float y)
{
	// bool	status;
	int		scale;
	int		i;
	int		j;

	// status = false;
	scale = get_game()->scale;
	x -= 1;
	y -= 1;
	i = 0;
	printf("%f, %f\n", x, y);
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (get_game()->map.map[(int)((x + i) / scale)][(int)((y + j) / scale)].type == WALL)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	player_walk(mlx_t *mlx)
{
	float		rad;
	float		x2;
	float		y2;
	float		*x1;
	float		*y1;
	t_player	temp;

	rad = (get_game()->player.dir - 90) * PI / 180.0;
	x1 = &get_game()->player.x;
	y1 = &get_game()->player.y;
	x2 = cos(rad);
	y2 = sin(rad);
	temp.x = *x1;
	temp.y = *y1;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		*x1 -= y2 * 3;
		*y1 += x2 * 3;
		pnf("%d, %d\n",((int)(*x1 / get_game()->scale)), ((int)(*y1 / get_game()->scale)));
		// pnf("%d\n", get_game()->map.map[(int)(*x1 / get_game()->scale) + 1][(int)(*y1 / get_game()->scale) + 1].type);
		// if ( == WALL)
		if (in_wall(*x1, *y1))
		{
			*x1 = temp.x;
			*y1 = temp.y;
		}
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		*x1 += y2 * 3;
		*y1 -= x2 * 3;
		if (get_game()->map.map[(int)*x1][(int)*y1].type == WALL)
		{
			*x1 = temp.x;
			*y1 = temp.y;
		}
	}
	else
		return ;
	get_game()->on_change = 0;
}

void	bind(void *mlx)
{
	player_walk(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		get_game()->player.dir -= 10;
		if (get_game()->player.dir <= 0)
			get_game()->player.dir = 360;
		else if (get_game()->player.dir >= 360)
			get_game()->player.dir = 0;
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		get_game()->player.dir += 10;
		if (get_game()->player.dir <= 0)
			get_game()->player.dir = 360;
		else if (get_game()->player.dir >= 360)
			get_game()->player.dir = 0;
	}
	else
		return ;
	get_game()->on_change = 0;
}

