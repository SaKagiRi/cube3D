/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:25:07 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/03 03:53:11 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	valid_str(char *str, unsigned int *col)
{
	unsigned int	len;
	unsigned int	tmp;

	len = 0;
	tmp = 0;
	while (*str == ' ')
	{
		len++;
		str++;
	}
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

void	lst_iter(t_list *raw_map, void (*f)(void *))
{
	t_list	*cur_row;
	t_list	*tmp;

	cur_row = raw_map;
	while (cur_row != NULL)
	{
		f(raw_map->content);
		tmp = cur_row;
		cur_row = cur_row->next;
		free(tmp);
	}
}

static void	add_to_queue(char *buf, t_mapvec *map)
{
	if (!map->raw_map)
	{
		// if (walloc(&map->raw_map, sizeof(t_list)) == MEM_ERR)
		// 	return ;
		map->raw_map = malloc(sizeof(t_list));
		if (!map->raw_map)
			return ;
		map->raw_map->content = ft_strdup(buf);
		map->raw_map->next = NULL;
		map->cur_row = map->raw_map;
	}
	else
	{
		// if (walloc(&map->cur_row->next, sizeof(t_list)) == MEM_ERR)
		// 	return ;
		map->cur_row->next = malloc(sizeof(t_list));
		if (!map->cur_row)
			return ;
		map->cur_row = map->cur_row->next;
		map->cur_row->content = ft_strdup(buf);
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
	char	*buf;
	void	*tmp;

	game = get_game();
	buf = get_next_line(fd);
	while (buf != NULL)
	{
		tmp = buf;
		buf = ft_strtrim(buf, "\n");
		free(tmp);
		if (!valid_str(buf, &map->col))
			game->err = MAP_ERR;
		add_to_queue(buf, &map->vecmap);
		free(buf);
		buf = get_next_line(fd);
		game->map.row++;
	}
}
