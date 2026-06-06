/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:49:21 by namatias          #+#    #+#             */
/*   Updated: 2026/06/06 02:12:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

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
	char		*player_view;
	int			player_x;
	int			player_y;
	int			total_x;
	int			total_y;
}				t_file;

typedef struct s_parser
{
	int			status;
	t_file		*file;
}				t_parser;

int		skip_space(char *line);
int		empty_line(char *line);
void	print_error(int status);
void	get_texture(char *line, t_parser *parser);
int		read_file(char *map_name, t_parser *parser);
int		check_args(int argc, char **argv, t_parser *status);
void	init_structs(t_parser *parser, t_file *file, t_texture *texture);

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*read_line(int fd, char *buffer, char *remaining);
char	*divide_line_and_save_rest(char *line);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif