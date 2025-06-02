/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:51:57 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/03 04:00:06 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_err	walloc(void *arg, size_t size)
{
	t_game	*game;

	game = get_game();
	arg = malloc(size);
	if (!arg)
		game->err = MEM_ERR;
	return (game->err);
}
