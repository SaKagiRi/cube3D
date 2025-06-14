/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:25:07 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/15 05:08:40 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	valid_str(char *str, int *col)
{
	int	len;
	int	tmp;

	len = 1;
	tmp = 0;
	while (*str++ == ' ')
		len++;
	while (*str != '\0' && in(*str, " 10NEWS"))
	{
		if (*str == ' ')
			tmp++;
		else if (in(*str, "01NEWS"))
		{
			len += tmp + 1;
			tmp = 0;
		}
		str++;
	}
	if (len > *col && (*str == '\0' || *str == '\n'))
		*col = len;
	else if (*str != '\0' && *str != '\n')
		return (0);
	return (1);
}

static void	add_to_queue(char *buf, t_mapvec *map)
{
	if (!map->raw_map)
	{
		if (walloc((void **)&map->raw_map, sizeof(t_list)) == MEM_ERR)
			return ;
		map->raw_map->content = buf;
		map->raw_map->next = NULL;
		map->cur_row = map->raw_map;
	}
	else
	{
		if (walloc((void **)&map->cur_row->next, sizeof(t_list)) == MEM_ERR)
			return ;
		map->cur_row = map->cur_row->next;
		map->cur_row->content = buf;
		map->cur_row->next = NULL;
	}
}

void	clear_list(t_list *row)
{
	t_list	*cur_row;
	void	*tmp;

	cur_row = row;
	while (cur_row != NULL)
	{
		tmp = cur_row->content;
		free(tmp);
		tmp = cur_row;
		cur_row = cur_row->next;
		free(tmp);
	}
}

void	get_queue(t_map *map, int fd)
{
	t_game	*game;
	void	*tmp;

	game = get_game();
	while (map->buf != NULL)
	{
		tmp = map->buf;
		map->buf = ft_strtrim(map->buf, "\n");
		free(tmp);
		if (!valid_str(map->buf, &map->col))
			game->err = MAP_ERR;
		add_to_queue(map->buf, &map->vecmap);
		if (game->err == MEM_ERR)
			return ;
		map->buf = get_next_line(fd);
		game->map.row++;
	}
}
