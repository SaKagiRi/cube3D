/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 06:09:36 by knakto            #+#    #+#             */
/*   Updated: 2025/06/13 06:18:19 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	allow_dir(t_game *game)
{
	if (game->player.dir <= 0)
		game->player.dir = 360 + game->player.dir;
	else if (game->player.dir >= 360)
		game->player.dir = 0 + game->player.dir;
}

bool	bindswing(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.dir -= game->move_cam_speed;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.dir += game->move_cam_speed;
	else
		return (0);
	game->on_change = false;
	allow_dir(game);
	return (1);
}
