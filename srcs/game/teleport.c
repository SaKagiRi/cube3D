/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:11:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:12:33 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"
#include <stdio.h>

void	reset_teleport(t_game *game, int sw)
{
	t_tp		*tp;

	tp = &game->teleport;
	if (sw == 1)
	{
		tp->tp_left.x = -1;
		tp->tp_left.y = -1;
		tp->side_left = -1;
	}
	else if (sw == 2)
	{
		tp->tp_right.x = -1;
		tp->tp_right.y = -1;
		tp->side_right = -1;
	}
}

void	set_teleport(t_game *game, t_player player, int sw)
{
	t_dist		hit;
	t_tp		*tp;

	hit = find_hit(player.dir_x, player.x, player.y);
	hit.side = set_side_wall(hit);
	tp = &game->teleport;
	if (sw == 1)
	{
		tp->tp_left.x = hit.block.x;
		tp->tp_left.y = hit.block.y;
		tp->side_left = hit.side;
	}
	else if (sw == 2)
	{
		tp->tp_right.x = hit.block.x;
		tp->tp_right.y = hit.block.y;
		tp->side_right = hit.side;
	}
	if (tp->tp_left.x == tp->tp_right.x && tp->tp_left.y == tp->tp_right.y \
&& tp->side_left == tp->side_right)
	{
		reset_teleport(game, 1);
		reset_teleport(game, 2);
	}
}

float	dif_portal(int side1, int side2)
{
	if ((side1 == NORTH && side2 == NORTH) \
|| (side1 == SOUTH && side2 == SOUTH))
		return (180);
	else if ((side1 == EAST && side2 == EAST) \
|| (side1 == WEST && side2 == WEST))
		return (180);
	if (side1 == NORTH && side2 == WEST)
		return (90);
	else if (side1 == NORTH && side2 == EAST)
		return (-90);
	if (side1 == WEST && side2 == NORTH)
		return (-90);
	else if (side1 == WEST && side2 == SOUTH)
		return (90);
	if (side1 == SOUTH && side2 == WEST)
		return (-90);
	else if (side1 == SOUTH && side2 == EAST)
		return (90);
	else if (side1 == EAST && side2 == NORTH)
		return (90);
	else if (side1 == EAST && side2 == SOUTH)
		return (-90);
	return (0);
}

void	teleport(t_game *game)
{
	t_vec2	tp;
	int		check;
	int		dif;

	if (game->teleport.side_left == -1 || game->teleport.side_right == -1)
		return ;
	check = 0;
	if (tp_check(game, game->player, 1))
	{
		tp = get_tp_point(game, 1);
		check = 1;
	}
	else if (tp_check(game, game->player, 2))
		tp = get_tp_point(game, 2);
	else
		return ;
	game->minimap.x += game->player.x - tp.x;
	game->minimap.y += game->player.y - tp.y;
	game->player.x = tp.x;
	game->player.y = tp.y;
	dif = dif_portal(game->teleport.side_left, game->teleport.side_right);
	if (check == 1)
		game->player.dir_x += dif;
	else
		game->player.dir_x -= dif;
}
