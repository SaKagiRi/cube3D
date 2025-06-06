/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/06/06 17:57:45 by kawaii           ###   ########.fr       */
=======
/*   Updated: 2025/06/06 18:30:06 by knakto           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "fcntl.h"
#include <stdio.h>

void	msg_exit(char *str, int num)
{
	ft_putstr_fd(str, 2);
	exit(num);
}

void	intit(void)
{
	get_game()->scale = 20;
	get_game()->first_render = true;
}

int	main(int argc, char **argv)
{
	t_game	*game;

	intit();
	parser(argc, argv);
	game = get_game();

	mlx();

	clear_tile(game->map.map, game->map.row);
	ft_exit(0);
}
