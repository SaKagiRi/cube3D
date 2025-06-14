/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:04:18 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 15:59:47 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "game.h"
#include "render.h"

void	mouse(t_game *game)
{
	int			x;
	int			y;
	float		dx;
	float		dy;

	mlx_get_mouse_pos(game->mlx, &x, &y);
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

void	jump(t_game *game)
{
	static int jump = -1;
	static bool on_down = false;

	if (!game->on_jump && jump == -1)
		return ;
	if (game->on_jump && jump == -1)
		jump = 0;
	if (jump < 30 && !on_down)
	{
		jump++;
		game->player.z += (30.0f - jump) / 1.3;
	}
	else if (jump > -1)
	{
		game->player.z -= (30.0f - jump) / 1.3;
		on_down = true;
		jump--;
	}
	if (jump == -1)
	{
		game->on_jump = false;
		game->player.z = 0;
		on_down = false;
	}
	game->on_change = false;
}

static bool	check_render(t_game *game)
{
	keybind(game);
	jump(game);
	mouse(game);
	if (game->on_change)
		return (true);
	mlx_delete_image(game->mlx, game->game_i);
	return (false);
}

static void	render(t_game *game)
{
	game->game_i = mlx_texture_to_image(game->mlx, game->game_t);
	mlx_image_to_window(game->mlx, game->game_i, 0, 0);
	fill_background(game->game_t, 0x000000);
	game->on_change = true;
}

void	put_cursor(t_game *game)
{
	int		i;

	i = 0;
	while (i <= 10)
		ft_texture(game->game_t, WIDTH / 2.0f - 5 + i++, HEIGHT / 2.0f, 0xFFFFFF);
	i = 0;
	while (i <= 10)
		ft_texture(game->game_t, WIDTH / 2.0f, HEIGHT / 2.0f - 5 + i++, 0xFFFFFF);
}

void	hook(void *data)
{
	t_game		*game;

	game = (t_game *)data;
	if (check_render(game))
		return ;
	put_game(game);
	put_map(game);
	put_player(game->game_t, game->player, 0x000000FF);
	put_cursor(game);
	render(game);
}
