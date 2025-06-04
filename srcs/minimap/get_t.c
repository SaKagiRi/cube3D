/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:12:55 by knakto            #+#    #+#             */
/*   Updated: 2025/06/04 15:12:33 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

t_map_pos	****get_t_map(void)
{
	static t_map_pos	***map = NULL;

	return (&map);
}

t_player_pos	*get_t_player(void)
{
	static t_player_pos	player;

	return (&player);
}
