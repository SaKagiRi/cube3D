/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 06:00:11 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 16:32:05 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	scale = SCALE;
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

static void	walk(t_game *game, float dir)
{
	t_vec2		next;
	float		speed;
	float		pdir;

	speed = game->player_speed;
	pdir = game->player.dir_x;
	if (dir == pdir || dir == pdir + 180)
		speed -= 0.12;
	next = wallcheck(game->player.x, game->player.y, dir, speed);
	if (next.x != game->player.x || next.y != game->player.y)
	{
		game->minimap.x -= next.x - game->player.x;
		game->minimap.y -= next.y - game->player.y;
	}
	game->player.x = next.x;
	game->player.y = next.y;
}

bool	key(int key)
{
	return (mlx_is_key_down(get_game()->mlx, key));
}

bool	bindwalk(t_game *game)
{
	if (key(MLX_KEY_W) && key(MLX_KEY_D))
		walk(game, game->player.dir_x + 125);
	else if (key(MLX_KEY_W) && key(MLX_KEY_A))
		walk(game, game->player.dir_x + 45);
	else if (key(MLX_KEY_S) && key(MLX_KEY_D))
		walk(game, game->player.dir_x + 225);
	else if (key(MLX_KEY_S) && key(MLX_KEY_A))
		walk(game, game->player.dir_x + 315);
	else if (key(MLX_KEY_W) && !key(MLX_KEY_S))
		walk(game, game->player.dir_x + 90);
	else if (key(MLX_KEY_S) && !key(MLX_KEY_W))
		walk(game, game->player.dir_x + 270);
	else if (key(MLX_KEY_D) && !key(MLX_KEY_A))
		walk(game, game->player.dir_x + 180);
	else if (key(MLX_KEY_A) && !key(MLX_KEY_D))
		walk(game, game->player.dir_x);
	else
		return (0);
	game->on_change = false;
	return (1);
}
