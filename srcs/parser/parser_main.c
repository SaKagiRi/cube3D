/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:18:16 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/06 17:45:38 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	init_file(char *path)
{
	t_game	*game;

	game = get_game();
	if (ft_strlen(ft_strrchr(path, '.')) != 4 \
		|| ft_strncmp(ft_strrchr(path, '.'), ".cub", 4))
	{
		game->err = FILE_ERR;
		ft_exit(1);
	}
	game->map.map_fd = open(path, O_RDONLY);
	if (game->map.map_fd < 0)
		game->err = FILE_ERR;
	return (game->err);
}

void	parser(int argc, char **argv)
{
	t_game	*game;

	game = get_game();
	if (argc != 2)
	{
		game->err = FILE_ERR;
		ft_exit(1);
	}
	if (init_file(argv[1]) == FILE_ERR)
		ft_exit(1);
	get_queue(&game->map, game->map.map_fd);
	if (game->err != OK)
	{
		clear_list(game->map.vecmap.raw_map);
		ft_exit(1);
	}
	parse_tile(&game->map);
	if (game->err != OK)
	{
		clear_list(game->map.vecmap.raw_map);
		if (game->err == CHARAC_ERR)
			clear_tile(game->map.map, game->map.row);
		ft_exit(1);
	}
}
