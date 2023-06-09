/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:25:07 by terabu            #+#    #+#             */
/*   Updated: 2023/07/03 11:24:56 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*set_texture(char *line)
{
	int		i;
	char	*path_texture;
	char	**set_data;

	set_data = ft_split(line, ' ');
	if (!set_data)
		exit_error(ERROR_MALLOC);
	i = 0;
	while (set_data[i])
	{
		if (i == 1)
		{
			path_texture = ft_strtrim(set_data[i], "\n");
			free_array(set_data);
			return (path_texture);
		}
		i++;
	}
	exit_error(ERROR_FORMAT);
	return (NULL);
}

void	set_rgb(int *file_rgb, char *line)
{
	char	**set_data;
	char	**set_rgb;
	int		i;

	set_data = ft_split(line, ' ');
	if (!set_data)
		exit_error(ERROR_MALLOC);
	if (!set_data[1])
		exit_error(ERROR_FORMAT);
	set_rgb = ft_split(set_data[1], ',');
	free_array(set_data);
	if (!set_rgb)
		exit_error(ERROR_MALLOC);
	i = 0;
	while (set_rgb[i])
	{
		file_rgb[i] = ft_atoi(set_rgb[i]);
		if (file_rgb[i] < 0 || 255 < file_rgb[i])
			exit_error(ERROR_MALLOC);
		i++;
	}
	free_array(set_rgb);
}

char	*get_element_line(t_file_data *file_data, char *word)
{
	int		i;
	int		word_cnt;
	char	*trim_line;

	i = 0;
	word_cnt = ft_strlen(word);
	while (file_data->line[i])
	{
		trim_line = ft_strtrim(file_data->line[i], " ");
		if (!ft_strncmp(trim_line, word, word_cnt))
		{
			free(trim_line);
			return (file_data->line[i]);
		}
		free(trim_line);
		i++;
	}
	return (NULL);
}

void	setting_element(t_file_data *file_data)
{
	char	*line;

	line = get_element_line(file_data, "NO ");
	if (line)
		file_data->texture_no = set_texture(line);
	line = get_element_line(file_data, "SO ");
	if (line)
		file_data->texture_so = set_texture(line);
	line = get_element_line(file_data, "WE ");
	if (line)
		file_data->texture_we = set_texture(line);
	line = get_element_line(file_data, "EA ");
	if (line)
		file_data->texture_ea = set_texture(line);
	line = get_element_line(file_data, "F ");
	if (line)
		set_rgb(file_data->floor_rgb, line);
	line = get_element_line(file_data, "C ");
	if (line)
		set_rgb(file_data->ceiling_rgb, line);
}
