/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 18:02:44 by kawaii           ###   ########.fr       */
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
void	init_player(char type, int x, int y);

void	parser(int argc, char **argv);

t_game	*get_game(void);

void	keyhook(void *arg);

void	print_map(mlx_t *mlx, mlx_texture_t *text);
void	bind(void *mlx);

t_color	new_color(int hex);
int		get_rgba(int r, int g, int b, int a);
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

void	ft_exit(int n);

#endif
