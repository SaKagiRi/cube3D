/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:45:04 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/14 02:24:53 by knakto           ###   ########.fr       */
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
		game->player.x = x - (get_game()->scale / 2);
		game->player.y = y - (get_game()->scale / 2);;
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
