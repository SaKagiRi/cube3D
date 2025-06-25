/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:18:16 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/25 23:41:26 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	init_file(int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		game->err = FILE_ERR;
		ft_exit(1);
	}
	if (ft_strlen(ft_strrchr(argv[1], '.')) != 4 \
|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4))
	{
		game->err = FILE_ERR;
		ft_exit(1);
	}
	game->map.map_fd = open(argv[1], O_RDONLY);
	if (game->map.map_fd < 0)
		game->err = FILE_ERR;
	return (game->err);
}

static void	get_attr(t_game *game)
{
	game->text.set = 0;
	game->text.n_txt = NULL;
	game->text.e_txt = NULL;
	game->text.w_txt = NULL;
	game->text.s_txt = NULL;
	game->text.c_color = new_color_hex(0x0);
	game->text.f_color = new_color_hex(0x0);
	read_attr(game, &game->map, game->map.map_fd);
	if (game->text.set != 6 || game->err == ATTR_ERR)
	{
		game->err = ATTR_ERR;
		clear_texture(&game->text);
		if (game->map.buf != NULL)
			clear_get_next_line(&game->map, game->map.map_fd);
		ft_exit(1);
	}
}

static void	get_content(t_game *game)
{
	get_queue(&game->map, game->map.map_fd);
	if (game->map.col > LIMIT_MAP_SIZE || game->map.row > LIMIT_MAP_SIZE)
		game->err = OVR_LM;
	if (game->err != OK)
	{
		clear_list(game->map.vecmap.raw_map);
		ft_exit(1);
	}
}

static void	get_tile(t_game *game)
{
	parse_tile(&game->map);
	if (game->err != OK)
	{
		clear_texture(&game->text);
		clear_list(game->map.vecmap.raw_map);
		ft_exit(1);
	}
	clear_list(game->map.vecmap.raw_map);
}

void	parser(int argc, char **argv)
{
	t_game	*game;

	game = get_game();
	if (init_file(argc, argv, game) == FILE_ERR)
		ft_exit(1);
	game->map.mode = ATTR_M;
	get_attr(game);
	get_content(game);
	get_tile(game);
	if (game->err != OK)
	{
		clear_texture(&game->text);
		clear_tile(game->map.map, game->map.row);
		ft_exit(1);
	}
	flood_fill(game->map.map, game, (int)(game->player.y / SCALE),
		(int)(game->player.x / SCALE));
	if (game->err != OK)
	{
		clear_texture(&game->text);
		clear_tile(game->map.map, game->map.row);
		ft_exit(1);
	}
}
