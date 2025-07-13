/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:29 by knakto            #+#    #+#             */
/*   Updated: 2025/07/13 16:58:57 by knakto           ###   ########.fr       */
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
int		all_in(char *str, char *set);

void	clear_queue(t_list *raw_map, void (*f)(void *));
void	lst_iter(t_list *raw_map, void (*f)(void *));
void	clear_list(t_list *row);
void	init_player(char type, int x, int y);

t_err	walloc(void **arg, size_t size);

void	read_attr(t_game *game, t_map *map, int fd);
void	get_queue(t_map *map, int fd);
void	parse_tile(t_map *map);

void	parser(int argc, char **argv);

void	clear_tile(t_tile **map, int row);

void	flood_fill(t_tile **tile, t_game *game, int y, int x);

void	mlx(void);
void	init_player(char type, int x, int y);

t_game	*get_game(void);

void	keyhook(void *arg);

t_color	new_color_hex(int hex);
t_color	new_color_rgba(u_char r, u_char g, u_char b, u_char a);
int		get_rgba(int r, int g, int b, int a);
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

void	clear_texture(t_text *text);
void	clear_get_next_line(t_map *map, int fd);
void	ft_exit(int n);

#endif
