/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:15:32 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/15 05:11:17 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	get_color(t_color *color, char *str)
{
	char	**option;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	option = ft_split(str, ',');
	while (option[i] != NULL && all_in(option[i], "0123456789,"))
		i++;
	if (i == 3)
	{
		r = ft_atoi(option[0]);
		g = ft_atoi(option[1]);
		b = ft_atoi(option[2]);
		*color = new_color_rgba(r, g, b, 0xFF);
		get_game()->text.set++;
	}
	else
		get_game()->err = ATTR_ERR;
	free_split(option);
}

static void	get_text(mlx_texture_t **text, char *path)
{
	if (*text)
	{
		get_game()->err = ATTR_ERR;
		return ;
	}
	*text = mlx_load_png(path);
	if (!*text)
	{
		get_game()->err = ATTR_ERR;
		return ;
	}
	get_game()->text.set++;
}

static void	assign_text(t_text *text_con, char *line)
{
	if (!ft_strncmp("NO ", line, 3))
		get_text(&text_con->n_txt, ft_strrchr(line, ' ') + 1);
	else if (!ft_strncmp("EA ", line, 3))
		get_text(&text_con->e_txt, ft_strrchr(line, ' ') + 1);
	else if (!ft_strncmp("WE ", line, 3))
		get_text(&text_con->w_txt, ft_strrchr(line, ' ') + 1);
	else if (!ft_strncmp("SO ", line, 3))
		get_text(&text_con->s_txt, ft_strrchr(line, ' ') + 1);
	else if (!ft_strncmp("F ", line, 2))
		get_color(&text_con->f_color, ft_strrchr(line, ' ') + 1);
	else if (!ft_strncmp("C ", line, 2))
		get_color(&text_con->c_color, ft_strrchr(line, ' ') + 1);
	else
		get_game()->err = ATTR_ERR;
}

void	read_attr(t_game *game, t_map *map, int fd)
{
	void	*tmp;

	map->buf = get_next_line(fd);
	while (map->buf != NULL || map->mode == ATTR_M)
	{
		tmp = map->buf;
		if (!all_in(map->buf, "\n"))
		{
			if (all_in(map->buf, " 10NEWS\n"))
			{
				map->mode = MAP_M;
				return ;
			}
			map->buf = ft_strtrim(map->buf, " \n");
			if (ft_strlen(map->buf))
				assign_text(&game->text, map->buf);
			free(map->buf);
		}
		free(tmp);
		map->buf = get_next_line(fd);
	}
}
