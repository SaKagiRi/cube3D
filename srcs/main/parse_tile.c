/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 03:29:11 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/05 10:56:13 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "stdlib.h"

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
	// res = (t_tile){(x + 1) * 100, y * 100, END};
	// if (type == '0' || in(type, "NEWS"))
	// 	res.type = PATH;
	// else if (type == '1')
	// 	res.type = WALL;
	// else if (type == ' ')
	// 	res.type = EMPT;
	tile->x = (x + 1) * 100;
	tile->y = y * 100;
	if (type == '0' || in(type, "NEWS"))
		tile->type = PATH;
	else if (type == '1')
		tile->type = WALL;
	else if (type == ' ')
		tile->type = EMPT;
	// return (res);
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
	size = sizeof(t_tile) * (map->col + 1);
	if (walloc((void **)&map->map, sizeof(t_tile *) * (map->row + 1)) == MEM_ERR)
		return (1);
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

	i = 1;
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
