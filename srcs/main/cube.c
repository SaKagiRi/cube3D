/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 17:04:48 by knakto           ###   ########.fr       */
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

int	init_file(char *path)
{
	t_game	*game;

	game = get_game();
	if (ft_strlen(ft_strrchr(path, '.')) != 4 \
		|| ft_strncmp(ft_strrchr(path, '.'), ".cub", 4))
	{
		game->err = MAP_ERR;
		msg_exit("Only file with .cub extension are allow.\n", 1);
	}
	game->map.map_fd = open(path, O_RDONLY);
	if (game->map.map_fd < 0)
		game->err = FILE_ERR;
	return (game->err);
}

void	parser(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		msg_exit("Nothing fill in argument.\n", 1);
	game = get_game();
	if (init_file(argv[1]) == FILE_ERR)
		msg_exit("Problem with entered path.\n", 1);
	get_queue(&game->map, game->map.map_fd);
	if (game->err != OK)
	{
		clear_list(game->map.vecmap.raw_map);
		msg_exit("Map contain invalid character.\n", 1);
	}
	parse_tile(&game->map);
	if (game->err != OK)
	{
		clear_list(game->map.vecmap.raw_map);
		if (game->err == CHARAC_ERR)
			clear_tile(game->map.map, game->map.row);
		msg_exit("Error during parsing.\n", 1);
	}
	clear_list(game->map.vecmap.raw_map);
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
	msg_exit("EXIT SUCCESSFULLY.\n", 0);
}
