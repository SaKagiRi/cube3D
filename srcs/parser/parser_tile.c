/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 03:29:11 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/05 12:11:17 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	clear_tile(t_tile **map, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(map[i++]);
	free(map);
}

static void	new_tile(t_tile *tile, char type, int x, int y)
{
	tile->x = (x + 1) * 100;
	tile->y = (y + 1) * 100;
	if (in(type, "NEWS"))
		init_player(type, tile->x, tile->y);
	else if (type == '0')
		tile->type = PATH;
	else if (type == '1')
		tile->type = WALL;
	else if (type == ' ')
		tile->type = EMPT;
}

static void	end_tile(t_tile *tile)
{
	*tile = (t_tile){-1, -1, END};
}

static int	init_tile(t_map *map)
{
	size_t			size;
	unsigned int	i;

	i = 0;
	size = sizeof(t_tile *) * (map->row + 1);
	if (walloc((void **)&map->map, size) == MEM_ERR)
		return (1);
	size = sizeof(t_tile) * (map->col + 1);
	while (i < map->row)
	{
		if (walloc((void **)&map->map[i], size) == MEM_ERR)
		{
			clear_tile(map->map, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	parse_tile(t_map *map)
{
	t_list		*cur;
	char		*con;
	int			i;
	int			j;

	i = 0;
	cur = map->vecmap.raw_map;
	if (init_tile(map))
		return ;
	while (cur)
	{
		j = 0;
		con = cur->content;
		while (con[j])
		{
			new_tile(&map->map[i][j], con[j], j, i);
			j++;
		}
		end_tile(&map->map[i][j]);
		cur = cur->next;
		i++;
	}
}
