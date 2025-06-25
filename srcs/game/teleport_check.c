/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:06:18 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:11:58 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	chech_teleport_side(int side, t_vec2 tp, t_player player)
{
	if (side == NORTH)
		return ((int)player.x >= (int)tp.x * SCALE + (SCALE / 4) \
&& (int)player.x <= (int)tp.x * SCALE + (SCALE * 3 / 4) \
&& (int)player.y == (int)tp.y * SCALE - 1);
	else if (side == SOUTH)
		return ((int)player.x >= (int)tp.x * SCALE + (SCALE / 4) \
&& (int)player.x <= (int)tp.x * SCALE + (SCALE * 3 / 4) \
&& (int)player.y == (int)(tp.y * SCALE + SCALE));
	else if (side == EAST)
		return ((int)player.y >= (int)tp.y * SCALE + (SCALE / 4) \
&& (int)player.y <= (int)tp.y * SCALE + (SCALE * 3 / 4) \
&& (int)player.x == (int)(tp.x * SCALE + SCALE));
	else if (side == WEST)
		return ((int)player.y >= (int)tp.y * SCALE + (SCALE / 4) \
&& (int)player.y <= (int)tp.y * SCALE + (SCALE * 3 / 4) \
&& (int)player.x == (int)tp.x * SCALE - 1);
	return (false);
}

bool	tp_check(t_game *game, t_player player, int sw)
{
	t_vec2	tp;
	int		side;

	tp = game->teleport.tp_right;
	if (sw == 1)
		tp = game->teleport.tp_left;
	side = game->teleport.side_right;
	if (sw == 1)
		side = game->teleport.side_left;
	return (chech_teleport_side(side, tp, player));
}

t_vec2	get_tp_point(t_game *game, int sw)
{
	t_vec2	tp;
	int		side;

	tp = game->teleport.tp_right;
	if (sw == 2)
		tp = game->teleport.tp_left;
	side = game->teleport.side_right;
	if (sw == 2)
		side = game->teleport.side_left;
	if (side == NORTH)
		return ((t_vec2){tp.x * SCALE + (SCALE / 2.f), tp.y * SCALE - 3});
	else if (side == SOUTH)
		return ((t_vec2){tp.x * SCALE + (SCALE / 2.f),
			tp.y * SCALE + SCALE + 2});
	else if (side == EAST)
		return ((t_vec2){tp.x * SCALE + SCALE + 2,
			tp.y * SCALE + (SCALE / 2.f)});
	else if (side == WEST)
		return ((t_vec2){tp.x * SCALE - 3, tp.y * SCALE + (SCALE / 2.f)});
	return ((t_vec2){game->player.x, game->player.y});
}
