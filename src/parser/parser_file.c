/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:05:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/04 23:19:47 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

	//o mapa existe!
	//Abrir e verificar informaçoes
		//Ler linha por linha (gnl ?)
		//Preencher struc com as inf.
			//DEVE TER:
				//Textura: no,so,we e ea
				//COR : F e C (chao e teto)
				//MAPA em si:
					//player: x, y, direcao q esta olhando (N, S, E ou W)
					//Cercado por 1 (parede)
					//Preenchido por 0 (esp vazio),

int	read_file(char *map_name, t_parser *parser)
{
	int		fd;
	char	*line;
	
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		parser->status = 4;
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		//Verifica se é uma linha vazia, se for pula para a prox linha
		if (empty_line(line))
		{
			get_texture(line, parser);
			// printf("Testando GNL: %s\n", line);
		}	
	//atualiza as infos, avança no arquivo, garante parada do looping
		line = get_next_line(fd);
	}
	close (fd);
	return (1);
}

void	get_texture(char *line, t_parser *parser)
{
	int		start;
	//char	end; 

	// TODO : Retirar o \n do final e o nome da variavel das strings e deixar apenas a info.
	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "NO", 2))
	{
		parser->file->texture->no = line;
	}
	else if (!ft_strncmp(line + start, "SO", 2))
	{
		parser->file->texture->so = line;
	}
	else if (!ft_strncmp(line + start, "WE", 2))
	{
		parser->file->texture->we = line;
	}
	else if (!ft_strncmp(line + start, "EA", 2))
	{
		parser->file->texture->ea = line;
	}
}
