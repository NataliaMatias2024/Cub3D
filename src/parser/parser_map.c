/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:31:33 by namatias          #+#    #+#             */
/*   Updated: 2026/06/08 22:33:47 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_map(char *line, t_parser *parser)
{
	char	*temp;

	temp = "Func only to test IF/ELSEs logic";
	if (line != NULL)
		line = temp;
	printf("%s\n", line);
	parser->status = 0;
}
