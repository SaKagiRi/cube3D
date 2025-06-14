/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 06:09:36 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 14:07:41 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	allow_dir(t_game *game)
{
	if (game->player.dir_x <= 0)
		game->player.dir_x = 360 + game->player.dir_x;
	else if (game->player.dir_x >= 360)
		game->player.dir_x = 0 + game->player.dir_x;
}

bool	bindswing(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.dir_x -= game->move_cam_speed;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.dir_x += game->move_cam_speed;
	else if (key(MLX_KEY_UP))
	{
		if (game->player.dir_y < 300)
		game->player.dir_y += 20;
	}
	else if (key(MLX_KEY_DOWN))
	{
		if (game->player.dir_y > -300)
			game->player.dir_y -= 20;
	}
	else
		return (0);
	game->on_change = false;
	allow_dir(game);
	return (1);
}
