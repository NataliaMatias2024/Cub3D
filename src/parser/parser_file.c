/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:05:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 14:00:58 by namatias         ###   ########.fr       */
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
static int	check_final_path(char *path, t_parser *parser);

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

	end = 0;
	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "NO", 2))
	{
		//SE alguma textura estiver duplicada retorna erro
		if (parser->file->texture->no != NULL)
		{
			parser->status = 6;
			return ;
		}
		//pula o nome da variavel + os espaços entre o nome e o inicio do caminho da textura
		start = start + 2;
		start = start + skip_space(line + start);
		if (!check_path_extension(line))
		{
			end = ft_strlen(line) - start;
			temp = ft_substr(line, start, end);
			if (check_final_path(temp, parser))
				parser->file->texture->no = ft_strdup(temp);
			free (temp);
		}
		else
			parser->status = 4;
	}
	else if (!ft_strncmp(line + start, "SO", 2))
	{
		if (parser->file->texture->so != NULL)
		{
			parser->status = 6;
			return ;
		}
		start = start + 2;
		start = start + skip_space(line + start);
		if (!check_path_extension(line))
		{
			end = ft_strlen(line) - start;
			temp = ft_substr(line, start, end);
			if (check_final_path(temp, parser))
				parser->file->texture->so = ft_strdup(temp);
			free (temp);
		}
		else
			parser->status = 4;
	}
	else if (!ft_strncmp(line + start, "WE", 2))
	{
		if (parser->file->texture->we != NULL)
		{
			parser->status = 6;
			return ;
		}
		start = start + 2;
		start = start + skip_space(line + start);
		if (!check_path_extension(line))
		{
			end = ft_strlen(line) - start;
			temp = ft_substr(line, start, end);
			if (check_final_path(temp, parser))
				parser->file->texture->we = ft_strdup(temp);
			free (temp);
		}
		else
			parser->status = 4;
	}
	else if (!ft_strncmp(line + start, "EA", 2))
	{
		if (parser->file->texture->ea != NULL)
		{
			parser->status = 6;
			return ;
		}
		start = start + 2;
		start = start + skip_space(line + start);
		if (!check_path_extension(line))
		{
			end = ft_strlen(line) - start;
			temp = ft_substr(line, start, end);
			if (check_final_path(temp, parser))
				parser->file->texture->ea = ft_strdup(temp);
			free (temp);
		}
		else
			parser->status = 4;
	}
}

//limpa espaços após o final da ultima string da linha E verifica se a exten está correta
static int	check_path_extension(char *path)
{
	int		size;
	int		result;

	size = ft_strlen(path);
	while(size > 4 && ft_isspace(path[size - 1]))
		size--;
	path[size] = '\0';
	if (size <= 4)
		result = 1;
	else
		result = ft_strncmp(path + (size - 4), ".png", 4);
	return (result);
}

//Garante que nao será aceito path com espaços no meio. Ex: ./path_to_the_eas    t_texture.png
static int	check_final_path(char *path, t_parser *parser)
{
	int i;
	int	fd;

	i = 0;
	while (path[i])
	{
		if(ft_isspace(path[i]))
		{
			parser->status = 5;
			return (0);
		}
		i++;
	}

	//Aqui em teoria ja esta td pronto para rodar na MLX
	//Ultima coisa é verificar se o caminho q isolamos realmente existe e temos permissao para acessa-lo
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		parser->status = 3;
		return (0);
	}
	close (fd);
	return (1);
}
