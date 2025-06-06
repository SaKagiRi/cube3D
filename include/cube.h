/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 17:36:53 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>

# include "kml.h"
# include "MLX42.h"
# include "game.h"
// #include "minimap.h"

# ifndef LIMIT_MAP_SIZE
#  define LIMIT_MAP_SIZE 100
# endif


int		in(char c, char	*set);

void	clear_queue(t_list *raw_map, void (*f)(void *));
void	lst_iter(t_list *raw_map, void (*f)(void *));
void	clear_list(t_list *row);
void	init_player(char type, int x, int y);

t_err	walloc(void **arg, size_t size);

void	get_queue(t_map *map, int fd);

void	clear_tile(t_tile **map, int row);
void	parse_tile(t_map *map);

void	mlx(void);

void	keyhook(void *arg);

void	print_map(mlx_t *mlx, mlx_texture_t *text);
void	bind(void *mlx);

#endif
