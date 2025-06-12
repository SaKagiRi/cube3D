/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:07:49 by knakto            #+#    #+#             */
/*   Updated: 2025/06/13 04:29:42 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "render.h"

t_vec2	wallcheck(float x, float y, float dir, float speed)
{
	t_vec2	next;
	float	i;
	float	rad;
	t_tile	**map;
	int		scale;

	i = 0;
	map = get_game()->map.map;
	scale = get_game()->scale;
	rad = dir * PI / 180;
	while (i < speed)
	{
		next.x = x;
		next.y = y;
		x += sin(rad) * i;
		y -= cos(rad) * i;
		if (map[(int)(y / scale)][(int)(x / scale)].type == WALL \
|| (map[(int)(next.y / scale)][(int)(x / scale)].type == WALL \
&& map[(int)(y / scale)][(int)(next.x / scale)].type == WALL))
			return (next);
		i += 0.1;
	}
	next.x = x;
	next.y = y;
	return (next);
}

void	walk(t_game *game, float dir)
{
	t_vec2		next;

	next = wallcheck(game->player.x, game->player.y, dir, game->player_speed);
	if (next.x != game->player.x || next.y != game->player.y)
	{
		game->minimap.x -= next.x - game->player.x;
		game->minimap.y -= next.y - game->player.y;
	}
	game->player.x = next.x;
	game->player.y = next.y;
}

bool	bindwalk(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		walk(game, game->player.dir + 90);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		walk(game, game->player.dir - 90);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		walk(game, game->player.dir - 180);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		walk(game, game->player.dir);
	else
		return (0);
	game->on_change = false;
	return (1);
}

bool	bindswing(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.dir -= game->move_cam_speed;
		if (game->player.dir <= 0)
			game->player.dir = 360;
		else if (game->player.dir >= 360)
			game->player.dir = 0;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.dir += game->move_cam_speed;
		if (game->player.dir <= 0)
			game->player.dir = 360;
		else if (game->player.dir >= 360)
			game->player.dir = 0;
	}
	else
		return (0);
	game->on_change = false;
	return (1);
}

bool	bindgame(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else
		return (0);
	game->on_change = false;
	return (1);
}

void	keybind(t_game	*game)
{
	bindwalk(game);
	bindgame(game);
	bindswing(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player_speed += 0.2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player_speed -= 0.2;
}
