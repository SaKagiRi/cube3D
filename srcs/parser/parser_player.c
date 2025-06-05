/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:45:04 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/05 11:50:38 by kawaii           ###   ########.fr       */
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
		game->player.x = x - 50;
		game->player.y = y - 50;
		if (type == 'N')
			game->player.dir = 0;
		if (type == 'E')
			game->player.dir = 90;
		if (type == 'W')
			game->player.dir = 270;
		if (type == 'S')
			game->player.dir = 180;
	}
	called++;
}
