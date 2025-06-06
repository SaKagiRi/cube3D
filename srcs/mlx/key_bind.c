/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:34:39 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 17:41:41 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "game.h"
#include <math.h>

void	player_work(mlx_t *mlx)
{
	float	rad;
	float	x2;
	float	y2;

	rad = (get_game()->player.dir - 90) * PI / 180.0;
	x2 = cos(rad);
	y2 = sin(rad);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		get_game()->player.x -= y2 * 3;
		get_game()->player.y += x2 * 3;
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		get_game()->player.x += y2 * 3;
		get_game()->player.y -= x2 * 3;
	}
	else
		return ;
	get_game()->on_change = 0;
}

void	bind(void *mlx)
{
	player_work(mlx);
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

