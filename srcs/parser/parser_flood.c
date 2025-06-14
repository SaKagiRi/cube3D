/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:08:37 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/14 16:23:33 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	flood_fill(t_tile **tile, t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y > game->map.row - 1 || x > game->map.col)
	{
		game->err = WALL_ERR;
		return ;
	}
	if (tile[y][x].type == EMPT || tile[y][x].type == END)
	{
		game->err = WALL_ERR;
		return ;
	}
	if (tile[y][x].type == PATH || tile[y][x].type == WALL)
		return ;
	if (tile[y][x].type == U_PATH)
		tile[y][x].type = PATH;
	flood_fill(tile, game, y + 1, x - 1);
	flood_fill(tile, game, y + 1, x);
	flood_fill(tile, game, y + 1, x + 1);
	flood_fill(tile, game, y, x + 1);
	flood_fill(tile, game, y, x - 1);
	flood_fill(tile, game, y - 1, x + 1);
	flood_fill(tile, game, y - 1, x);
	flood_fill(tile, game, y - 1, x - 1);
}
