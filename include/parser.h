/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:49:21 by namatias          #+#    #+#             */
/*   Updated: 2026/06/13 00:13:51 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/* 									INCLUDES                                  */
/* ************************************************************************** */
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

/* ************************************************************************** */
/* 									STRUCTURES                                */
/* ************************************************************************** */
typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}			t_texture;

typedef struct s_file
{
	t_texture	*texture;
	int			color_floor;
	int			color_ceiling;
	char		**map;
	char		player_view;
	int			player_row;
	int			player_col;
	int			total_row;
	int			total_col;
}				t_file;

typedef struct s_parser
{
	int			status;
	int			map_started;
	int			map_ended;
	t_file		*file;
	t_dlist		*temp_map;
}				t_parser;

/* ************************************************************************** */
/* 									PROTOTYPES                                */
/* ************************************************************************** */

/* -- Argument Verification & Initialization (parser_args.c / parser_utils.c) */
int		check_args(int argc, char **argv, t_parser *parser);
void	init_structs(t_parser *parser, t_file *file, t_texture *texture);

/* --- File Reading Workflow (parser_file.c) -------------------------------- */
int		read_file(char *map_name, t_parser *parser);
int		check_permission(char *file, t_parser *parser);

/* --- Element Extractors (parser_texture.c / parser_color.c) --------------- */
void	get_texture(char *line, t_parser *parser);
void	get_color(char *line, t_parser *parser);

/* --- Map Handling & Matrix Building (parser_map.c) ------------------------ */
void	append_map_line(char *line, t_parser *parser);
int		build_map_matrix(t_parser *parser, int fd);

/* --- Map Validation & Flood Fill (parser_map_utils.c) --------------------- */
int		check_map_info(t_file *file);
char	**clone_map(t_parser *parser, t_file *file);
int		trigger_flood_fill(t_file *file, char **map_copy);

/* --- Memory Deallocation & Cleanup (clean_free.c) ------------------------- */
void	free_split(char **splited);
void	clean_all(t_parser *parser);

/* --- Error Handling & Utilities (parser_error_msg.c / parser_utils.c) ----- */
void	print_error(int status);
int		empty_line(char *line);
int		skip_space(char *line);

#endif
