/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:45:04 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/14 14:36:06 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_player(char type, int x, int y)
{
	static int	called;
	t_game		*game;

	game = get_game();
	if (called)
	{
		game->err = CHARAC_ERR;
		return ;
	}
	if (in(type, "NEWS"))
	{
		game->player.x = x - (SCALE / 2);
		game->player.y = y - (SCALE / 2);;
		if (type == 'N')
			game->player.dir_x = 0;
		if (type == 'E')
			game->player.dir_x = 90;
		if (type == 'W')
			game->player.dir_x = 270;
		if (type == 'S')
			game->player.dir_x = 180;
	}
	called++;
}
