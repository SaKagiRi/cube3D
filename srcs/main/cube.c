/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 16:23:51 by kawaii           ###   ########.fr       */
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
	get_game()->first_render = true;
	// get_game()->scale = 10;
	get_game()->player_speed = 0.4;
	get_game()->player_size = SCALE / 2;
	get_game()->move_cam_speed = 5;
	get_game()->minimap.x = 0;
	get_game()->minimap.y = 0;
}

int	main(int argc, char **argv)
{
	t_game	*game;

	intit();
	parser(argc, argv);
	game = get_game();

	mlx();

	clear_tile(game->map.map, game->map.row);
	ft_exit(0);
}
