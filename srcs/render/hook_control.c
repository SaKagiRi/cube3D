/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:04:18 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 14:32:41 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"

void	mouse(t_game *game)
{
	int		x;
	int		y;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return ;
	if (x > WIDTH / 2)
		game->player.dir_x += 1;
	else if (x < WIDTH / 2)
		game->player.dir_x -= 1;
	if (y > HEIGHT / 2)
	{
		if (game->player.dir_y < 300)
			game->player.dir_y += 1;
	}
	else if (y < HEIGHT / 2)
	{
		if (game->player.dir_y > -300)
			game->player.dir_y -= 1;
	}
	// mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
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
		game->player.z += 10;
	}
	else if (jump > -1)
	{
		game->player.z -= 10;
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
	// mouse(game);
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

void	hook(void *data)
{
	t_game		*game;

	game = (t_game *)data;
	if (check_render(game))
		return ;
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	put_map(game);
	put_player(game->game_t, game->player, 0x000000FF);
	// ray(game->player.x, game->player.y, game->player.dir_x);
	put_game(game);
	// put_fov(game);
	render(game);
	printf("speed: %f\n", game->player_speed);
}
