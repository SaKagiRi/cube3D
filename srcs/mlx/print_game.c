/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:37:04 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 18:39:54 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "drawline.h"
#include "ray.h"

// void	print_game()
// {
// 	t_vec2		hit;
// 	t_player	player;
// 	float		rad;
// 	float		i;
//
// 	player = get_game()->player;
// 	rad = player.dir * PI / 180;
// 	hit = find_hit(rad + 0.4, player.x, player.y);
// 	bresenham(text, (t_point){0x000000, player.x, player.y, 0}, (t_point){0x000000, hit.x, hit.y, 0});
// 	hit = find_hit(rad - 0.4, player.x, player.y);
// 	bresenham(text, (t_point){0x000000, player.x, player.y, 0}, (t_point){0x000000, hit.x, hit.y, 0});
// 	printf("->>%f\n", distance(player.x, player.y, hit.x, hit.y));
// 	i = -0.39;
// 	while (i < 0.39)
// 	{
// 		hit = find_hit(rad + i, player.x, player.y);
// 		bresenham(text, (t_point){0xAAAADD, player.x, player.y, 0}, (t_point){0xAAAADD, hit.x, hit.y, 0});
// 		i += 0.001;
// 	}
// 	pnf("aaa\n");
// }
