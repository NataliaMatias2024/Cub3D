/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 17:57:05 by namatias          #+#    #+#             */
/*   Updated: 2026/06/08 20:09:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_path_extension(char *path);
static int	check_final_path(char *path, t_parser *parser);
static void	check_text(int start, t_parser *parser, char *line, char **coord);

//Limpar o começo da line recebida garante que:
//As analises sejam mais simples e precisas
//Nao precise analisar e manipular o mesmo trecho varias vezes
//Deixa a string final no padrao exigido pela MLX

//Além disso a norminette exige funçoes de no max 25
//se fazendo necessário funçoes auxiliares como a check_text
void	get_texture(char *line, t_parser *parser)
{
	int		start;

	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "NO", 2))
		check_text(start, parser, line, &parser->file->texture->no);
	else if (!ft_strncmp(line + start, "SO", 2))
		check_text(start, parser, line, &parser->file->texture->so);
	else if (!ft_strncmp(line + start, "WE", 2))
		check_text(start, parser, line, &parser->file->texture->we);
	else if (!ft_strncmp(line + start, "EA", 2))
		check_text(start, parser, line, &parser->file->texture->ea);
}

//Texturas duplicadas são considerados erros pelo subject do projeto
static void	check_text(int start, t_parser *parser, char *line, char **coord)
{
	int		end;
	char	*temp;

	end = 0;
	if (*coord != NULL)
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
			*coord = temp;
		else
			free (temp);
	}
	else
		parser->status = 4;
}

//Além de chegar a extensão tambem limpa a porçao final da string
//seguindo a lógica da limpeza inicial da funçao anterior
static int	check_path_extension(char *path)
{
	int		size;
	int		result;

	size = ft_strlen(path);
	while (size > 4 && ft_isspace(path[size - 1]))
		size--;
	path[size] = '\0';
	if (size <= 4)
		result = 1;
	else
		result = ft_strncmp(path + (size - 4), ".png", 4);
	return (result);
}

//Garante que nao será aceito path com espaços no meio. 
//Ex: ./path_to_the_eas    t_texture.png <- Invalido
//Realizando tbm a ultima análise:
	// O arquivo do path existe E pode ser lido!
static int	check_final_path(char *path, t_parser *parser)
{
	int	i;
	int	fd;

	i = 0;
	while (path[i])
	{
		if (ft_isspace(path[i]))
		{
			parser->status = 5;
			return (0);
		}
		i++;
	}
	fd = check_permission(path, parser);
	if (fd == -1)
		return (0);
	close (fd);
	return (1);
}
