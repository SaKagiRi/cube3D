/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_addmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:32:58 by knakto            #+#    #+#             */
/*   Updated: 2025/06/04 15:18:59 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <stdlib.h>

int		len_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	print(void)
{
	t_map_pos	***map;
	int		i;
	int		j;

	i = 0;
	map = *get_t_map();
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != NULL)
		{
			if (map[i][j]->x == 0)
				pnf("\n");
			// pnf("%d,%d ", map[i][j]->x, map[i][j]->y);
			if (map[i][j]->type == WALL)
				pnf("W");
			if (map[i][j]->type == FLOOR)
				pnf("F");
			if (map[i][j]->type == VOID)
				pnf("V");
			j++;
		}
		i++;
	}
}

void	addmap(char	*map)
{
	char	**temp;
	int		i;
	int		j;
	t_map_pos	***big;

	temp = ft_split(map, '\n');
	if (!temp)
		return ;
	big = malloc(sizeof(t_map_pos **) * (len_arg(temp) + 1));
	i = 0;
	while (temp[i])
	{
		big[i] = malloc(sizeof(t_map_pos *) * (ft_strlen(temp[i]) + 1));
		j = 0;
		while (temp[i][j])
		{
			big[i][j] = malloc(sizeof(t_map_pos));
			big[i][j]->x = j;
			big[i][j]->y = i;
			if (temp[i][j] == ' ')
				big[i][j]->type = VOID;
			else if (temp[i][j] == '1')
				big[i][j]->type = WALL;
			else if (temp[i][j] == '0')
				big[i][j]->type = FLOOR;
			else if (temp[i][j] == 'p')
			{
				big[i][j]->type = FLOOR;
				get_t_player()->x = j;
				get_t_player()->y = i;
				get_t_player()->dir = 0;
			}
			j++;
		}
		big[i][j] = NULL;
		i++;
	}
	big[i] = NULL;
	*get_t_map() = big;
}
