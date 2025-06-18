/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:04:49 by knakto            #+#    #+#             */
/*   Updated: 2025/06/17 21:20:54 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "render.h"

static bool	check_start_display(t_game *game, int x, int y)
{
	static bool	start = true;

	if (start && x != WIDTH / 2 && y != HEIGHT / 2)
	{
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
		return (start);
	}
	start = false;
	return (start);
}

bool	init_mouse(t_game *game)
{
	if (game->mouse == -1)
		return (1);
	else if (game->mouse == -2)
		return (0);
	else if (game->mouse == 1)
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		game->mouse = -1;
		return (1);
	}
	else
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		game->mouse = -2;
		return (0);
	}
}

void	mouse(t_game *game)
{
	int			x;
	int			y;
	float		dx;
	float		dy;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (!init_mouse(game) || check_start_display(game, x, y))
		return ;
	dx = x - (WIDTH / 2.0f);
	dy = y - (HEIGHT / 2.0f);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	if ((x == WIDTH / 2 && y == HEIGHT / 2))
		return ;
	if (x != WIDTH / 2)
		game->player.dir_x += dx / (110 - (game->mouse_sen * 100));
	if (y != HEIGHT / 2)
	{
			game->player.dir_y -= dy / 2;
		if (!(game->player.dir_y < 600 && game->player.dir_y > -600))
			game->player.dir_y += dy / 2;
	}
	game->on_change = false;
}
