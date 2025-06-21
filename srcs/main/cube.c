/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
/*   Updated: 2025/06/20 16:23:24 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "fcntl.h"
#include <stdio.h>

void	msg_exit(char *str, int num)
{
	ft_putstr_fd(str, 2);
	exit(num);
}

void	intit(void)
{
	t_game *g;

	g = get_game();
	g->first_render = true;
	g->player_speed = 0.35;
	g->player_size = SCALE / 2;
	g->move_cam_speed = 1;
	g->minimap.x = 0;
	g->minimap.y = 0;
	g->fog = true;
	g->fov = 45;
	g->mouse = 1;
}

int	main(int argc, char **argv)
{
	t_game	*game;

	intit();
	parser(argc, argv);
	game = get_game();

	mlx();

	clear_tile(game->map.map, game->map.row);
	clear_texture(&game->text);
	ft_exit(0);
}
