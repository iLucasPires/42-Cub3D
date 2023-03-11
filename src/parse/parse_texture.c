/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:36:11 by rlins             #+#    #+#             */
/*   Updated: 2023/03/11 11:47:06 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	*parse_text_path(char *row, int i);

bool parse_tex_dir(t_texture_det *text_det, char *row, int i)
{
	if (row[2] != ' ')
		return (false);
	if (row[i] == 'N' && row[i + 1] == 'O' && text_det->north == NULL)
		text_det->north = parse_text_path(row, (i + 3));
	else if (row[i] == 'S' && row[i + 1] == 'O' && text_det->south == NULL)
		text_det->south = parse_text_path(row, (i + 3));
	else if (row[i] == 'W' && row[i + 1] == 'E' && text_det->west == NULL)
		text_det->west = parse_text_path(row, (i + 3));
	else if (row[i] == 'E' && row[i + 1] == 'A' && text_det->east == NULL)
		text_det->east = parse_text_path(row, (i + 3));
	else
		return (false); // TODO: Testar dando erro aqui, como que se comportará
	return (true);
}

bool parse_tex_color()
{
	return (true);
}

/**
 * @brief Extract the path of the Texture to be used. Calloc of -3 (2 char and
 * white space, but +1 to end string)
 * @param string
 * @param i Start index in a row with the value of texture
 * @return char* = Row with a value of texture
 */
static char	*parse_text_path(char *row, int i)
{
	int		len;
	char	*path;
	int		j;

	j = 0;
	// TODO: Pensar se tem que tratar espaço,q uebra de linha do usuário
	len = ft_strlen(row);
	path = ft_calloc(len - 2, sizeof(char));
	if (!path)
		return (NULL);
	while (row[i] && (is_white_space(row[i]) == false))
		path[j++] = row[i++];
	path[j] = '\0';
	return (path);
}
