/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:07:11 by knakto            #+#    #+#             */
/*   Updated: 2025/06/25 23:38:59 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	on_jump(t_game *game, int *jump, bool *on_down)
{
	float	jump_height;

	jump_height = 60;
	if (*jump < jump_height && !*on_down)
	{
		*jump += 8;
		game->player.z += (jump_height - *jump) / 1.5;
	}
	else if (*jump > -10)
	{
		game->player.z -= (jump_height - *jump) / 1.5;
		*on_down = true;
		*jump -= 8;
	}
}

void	jump(t_game *game)
{
	static int	jump = -1;
	static bool	on_down = false;

	if (!game->on_jump && jump == -1)
		return ;
	if (game->on_jump && jump == -1)
		jump = 0;
	on_jump(game, &jump, &on_down);
	if (jump <= -1)
	{
		jump = -1;
		game->on_jump = false;
		game->player.z = 0;
		on_down = false;
	}
	game->on_change = false;
}
