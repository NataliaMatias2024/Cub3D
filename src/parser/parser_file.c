/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:05:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 00:53:08 by namatias         ###   ########.fr       */
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
static int	check_path_extension(char *path);

int	read_file(char *map_name, t_parser *parser)
{
	int		fd;
	char	*line;
	
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		parser->status = 3;
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		//Verifica se é uma linha vazia E se nao houve nenhum erro ao coletar textura e cor
		if (!empty_line(line) && parser->status == 0)
		{
			get_texture(line, parser);
			// printf("Testando GNL: %s\n", line);
		}
		else if (parser->status != 0)//caso de erro liberamos a linha para n ocorrer leak e retornamos 0, encerrando looping
		{
			free(line);
			return (0);
		}
	//atualiza as infos, avança no arquivo, garante parada do looping
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (1);
}

void	get_texture(char *line, t_parser *parser)
{
	int		start;
	int		end; 
	char	*temp;

	// TODO : Retirar o \n do final e o nome da variavel das strings e deixar apenas a info.
	end = 0;
	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "NO", 2))
	{
		//pula o nome da variavel + os espaços entre o nome e o inicio do caminho da textura
		start = start + 2;
		start = start + skip_space(line + start);
		printf("start pós segundo skip = %d\n", start);

		if (!check_path_extension(line))
		{
			end = ft_strlen(line);
			printf("end final = %d\n", end);
			temp = ft_substr(line, start, end);
			parser->file->texture->no = ft_strdup(temp);
			free (temp);
		}
		else
			parser->status = 4;	
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

//limpa espaços após o final da ultima string da linha E verifica se a exten está correta
static int	check_path_extension(char *path)
{
	int		size;
	int		result;

	size = ft_strlen(path);
	printf("size inicial = %d", size);
	while(size > 4 && ft_isspace(path[size - 1]))
		size--;
	printf("size final = %d", size);
	path[size] = '\0';
	if (size <= 4)
		result = 1;
	else
		result = ft_strncmp(path + (size - 4), ".png", 4);
	return (result);
}

