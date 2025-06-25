/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:32:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:34:45 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	get_block_side(float center_x, float center_y, float hit_x, float hit_y)
{
	float	dx;
	float	dy;

	dx = hit_x - center_x;
	dy = hit_y - center_y;
	if (fabs(dx) >= fabs(dy))
	{
		if (dx > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (dy > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	set_side_wall(t_dist hit)
{
	float	center_x;
	float	center_y;

	center_x = (hit.block.x * SCALE) + (SCALE / 2.0f);
	center_y = (hit.block.y * SCALE) + (SCALE / 2.0f);
	if (hit.block.x == 0 && hit.block.y == 0)
		return (-1);
	return (get_block_side(center_x, center_y, hit.hit.x, hit.hit.y));
}

mlx_texture_t	*get_side(t_game *game, int side)
{
	if (side == NORTH)
		return (game->text.n_txt);
	else if (side == WEST)
		return (game->text.w_txt);
	else if (side == EAST)
		return (game->text.e_txt);
	else if (side == SOUTH)
		return (game->text.s_txt);
	return (NULL);
}
