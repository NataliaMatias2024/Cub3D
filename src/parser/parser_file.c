/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:05:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/07 19:20:41 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
Ponto de partida - check points
	o mapa existe e pode abri-lo!
	Abrir e verificar informaçoes
		Ler linha por linha (gnl ?)
		Preencher struc com as inf.
			DEVE TER:
				Textura: no,so,we e ea
				COR : F e C (chao e teto)
				MAPA em si:
					player: x, y, direcao q esta olhando (N, S, E ou W)
					Cercado por 1 (parede)
					Preenchido por 0 (esp vazio),
*/

//Conforme as linhas de texto são lidas as informaçoes sao isoladas,
//tratadas e salvas na struct de parser
//Erros devem interromper o programa e avisar a gnl que deve encerrar e liberar memoria
int	read_file(char *map_name, t_parser *parser)
{
	int		fd;
	char	*line;

	fd = check_permission(map_name, parser);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!empty_line(line) && parser->status == 0)
		{
			get_texture(line, parser);
		}
		else if (parser->status != 0)
		{
			free(line);
			get_next_line(-1);
			close (fd);
			return (0);
		}
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (1);
}
