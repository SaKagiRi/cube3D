/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:07:49 by knakto            #+#    #+#             */
/*   Updated: 2025/06/10 22:23:18 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "game.h"
#include "render.h"

void	set_outcode()
{
	int			scale;
	t_tile		**map;
	int			x;
	int			y;
	t_player	*player;

	scale = get_game()->scale;
	map = get_game()->map.map;
	player = &get_game()->player;
	x = (int)player->x % scale;
	y = (int)player->y % scale;
	if (x == scale - 1 || x == 0 || y == scale - 1 || y == 0)
	{
		x = (int)player->x / scale;
		y = (int)player->y / scale;
		player->outcode = 0;
		if (map[y - 1][x].type == PATH)
			player->outcode |= 0b1000;
		if (map[y][x + 1].type == PATH)
			player->outcode |= 0b0100;
		if (map[y + 1][x].type == PATH)
			player->outcode |= 0b0010;
		if (map[y][x - 1].type == PATH)
			player->outcode |= 0b0001;
	}
}

void	revers_dir(int *dir, int sw)
{
	int		d;
	int		swing;

	d = *dir;
	swing = 0;
	if (sw == 1)
		swing = 180;
	else if (sw == 2)
		swing = 270;
	else if (sw == 3)
		swing = 90;
	d -= swing;
	if (d < 0)
		d = 360 + d;
	*dir = d;
}

bool	can_walk_y(int sw)
{
	int			y;
	int			dir;
	t_game		*game;
	
	game = get_game();
	y = (int)game->player.y % game->scale;
	dir = (int)game->player.dir;
	if (sw)
		revers_dir(&dir, sw);
	if (!(y == game->scale - 1 || y == 0))
		return (true);
	if (dir > 180 && dir < 360)
	{
		if (y != 0 || game->player.outcode & 0b1000)
			return (true);
		return (false);
	}
	if (!(dir >= 180 && dir <= 360))
	{
		if (y != game->scale - 1 || game->player.outcode & 0b0010)
			return (true);
		return (false);
	}
	return (true);
}

bool	can_walk_x(int sw)
{
	int			x;
	int			dir;
	t_game		*game;
	
	game = get_game();
	x = (int)game->player.x % game->scale;
	dir = (int)game->player.dir;
	if (sw)
		revers_dir(&dir, sw);
	if (!(x == game->scale - 1 || x == 0))
		return (true);
	if (dir > 90 && dir < 270)
	{
		if (x != 0 || game->player.outcode & 0b0001)
			return (true);
		return (false);
	}
	if (!(dir >= 90 && dir <= 270))
	{
		if (x != game->scale - 1 || game->player.outcode & 0b0100)
			return (true);
		return (false);
	}
	return (true);
}

bool	bindwalk_A(t_game *game)
{
	float		rad;

	rad = (game->player.dir) * PI / 180;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) \
&& can_walk_x(2) && can_walk_y(2))
	{
		game->minimap.x += sin(rad) * game->player_speed;
		game->minimap.y -= cos(rad) * game->player_speed;
		game->player.x -= sin(rad) * game->player_speed;
		game->player.y += cos(rad) * game->player_speed;
		set_outcode();
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) \
&& can_walk_x(3) && can_walk_y(3))
	{
		game->minimap.x -= sin(rad) * game->player_speed;
		game->minimap.y += cos(rad) * game->player_speed;
		game->player.x += sin(rad) * game->player_speed;
		game->player.y -= cos(rad) * game->player_speed;
		set_outcode();
	}
	else
		return (0);
	game->on_change = false;
	return (1);
}

bool	bindwalk(t_game *game)
{
	float		rad;

	rad = (game->player.dir - 90) * PI / 180;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) \
&& can_walk_x(0) && can_walk_y(0))
	{
		game->minimap.x += sin(rad) * game->player_speed;
		game->minimap.y -= cos(rad) * game->player_speed;
		game->player.x -= sin(rad) * game->player_speed;
		game->player.y += cos(rad) * game->player_speed;
		set_outcode();
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) \
&& can_walk_x(1) && can_walk_y(1))
	{
		game->minimap.x -= sin(rad) * game->player_speed;
		game->minimap.y += cos(rad) * game->player_speed;
		game->player.x += sin(rad) * game->player_speed;
		game->player.y -= cos(rad) * game->player_speed;
		set_outcode();
	}
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
	bindwalk_A(game);
	bindwalk(game);
	bindgame(game);
	bindswing(game);
}
