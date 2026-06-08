/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:35:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/08 20:29:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_str_is_numeric(char *str, t_parser *parser);
static int	ft_check_atol(char **splited, t_parser *parser);
static int	check_free_split(char **splited, t_parser *parser, int *color);
static void	check_color(int start, t_parser *parser, char *line, int *color);

// Enviamos o endereço de memória da variável na struct (&color_floor/ceiling)
// para permitir a modificação direta do valor original sem precisar de retornos
void	get_color(char *line, t_parser *parser)
{
	int		start;

	start = 0;
	start = skip_space(line);
	if (!ft_strncmp(line + start, "F", 1))
		check_color(start, parser, line, &parser->file->color_floor);
	else if (!ft_strncmp(line + start, "C", 1))
		check_color(start, parser, line, &parser->file->color_ceiling);
}

// Remove espaços finais e quebras de linha residuais antes de realizar o split
// garantindo uma conversão limpa pelo ft_atol e ft_atoi
static void	check_color(int start, t_parser *parser, char *line, int *color)
{
	char	**rgb;
	int		end;

	if (*color != -1)
	{
		parser->status = 7;
		return ;
	}
	start = start + 1;
	start = start + skip_space(line + start);
	end = ft_strlen(line);
	while (line[end - 1] && ft_isspace(line[end - 1]))
		end--;
	line[end] = '\0';
	rgb = ft_split((line + start), ',');
	if (!check_free_split(rgb, parser, color))
		free_split(rgb);
}

//O Formato de cor exigido pela minilibx é em hexadecimal ou TRGB (acrescenta a faixa de transparencia)
//Primeiro garantimos que foram recebidos apenas R G B (3 faixas)
//isolamos cada uma e só depois geramos o TRGB
//Nesse projeto tanto o chao quanto o teto nao terão transparencia e a faixa T será sempre 0
//Por isso omiti T no bitwise pois o C automaticamente preenche esses bits com zeros 
static int	check_free_split(char **splited, t_parser *parser, int *color)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	trgb;

	i = 0;
	while (splited[i])
		i++;
	if (i != 3)
	{
		parser->status = 9;
		return (0);
	}
	if (!ft_check_atol(splited, parser))
		return (0);
	r = ft_atoi(splited[0]);
	g = ft_atoi(splited[1]);
	b = ft_atoi(splited[2]);
	trgb = r << 16 | g << 8 | b;
	*color = trgb;
	free_split(splited);
	return (1);
}

static int	ft_check_atol(char **splited, t_parser *parser)
{
	int	i;
	int	temp;

	i = 0;
	while (splited[i] && i <= 2)
	{
		temp = ft_atol(splited[i]);
		if ((temp >= 0 && temp <= 255) && ft_str_is_numeric(splited[i], parser))
			i++;
		else
		{
			parser->status = 8;
			return (0);
		}
	}
	if (i != 3)
	{
		parser->status = 9;
		return (0);
	}
	return (1);
}

static int	ft_str_is_numeric(char *str, t_parser *parser)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			parser->status = 9;
			return (0);
		}
	}
	return (1);
}
