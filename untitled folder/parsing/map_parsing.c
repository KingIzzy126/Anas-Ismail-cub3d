/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:16:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/18 20:52:58 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	surrounded_map(char *test_line_map, t_info *info)
{
	int	i;

	i = 0;
	if (info->is_hv_err == 1)
		return ;
	if (info->is_f_m_l == 0 || info->is_f_m_l == 2)
	{
		while (test_line_map[i])
		{
			if (!(test_line_map[i] == '1' || test_line_map[i] == ' '))
				exitmassege("You Must Arround The Map By Walls\n", info);
			i++;
		}
		info->is_f_m_l++;
	}
	if (!(test_line_map[0] == '1' || test_line_map[0] == ' '))
		exitmassege("You Must Arround The Map By Walls\n", info);
	if (!(test_line_map[ft_strlen(test_line_map) - 1] == '1'
			|| test_line_map[ft_strlen(test_line_map) - 1] == ' '))
		exitmassege("You Must Arround The Map By Walls\n", info);
}

void	replace_spaces2one(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == ' ')
				info->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	after_get_map(t_info *info)
{
	if (info->is_hv_err == 1)
		return ;
	if (info->is_hv_plr == 0)
		exitmassege("You Must Have A Player\n", info);
	if (check_zero_player_allowed(info) == 1)
	{
		exitmassege("invalid map data\n", info);
		return ;
	}
	if (check_spaces_allowed(info) == 1)
	{
		exitmassege("spaces not allowed in this way\n", info);
		return ;
	}
	replace_spaces2one(info);
}

int	fill_header_map_data(int fd, t_info *info)
{
	char	*test_line_map;

	test_line_map = NULL;
	while (1)
	{
		test_line_map = free_string(test_line_map);
		test_line_map = get_next_line(fd, info);
		if (!test_line_map)
			break ;
		if (info->number_of_elemnts < 6)
			header_parsing(&test_line_map, info);
		else if (info->is_hv_err != 1)
		{
			if (info->x_lngth_mp == -1 && !test_line_map[0])
				continue ;
			info->map = add_in_array2d(&info->map, test_line_map);
			info->y_lngth_mp++;
			if (info->x_lngth_mp == -1)
				info->x_lngth_mp = ft_strlen(test_line_map);
			data_map(test_line_map, info);
			surrounded_map(test_line_map, info);
		}
	}
	return (info->is_hv_err);
}

void	map_pars_main(int fd, t_info *info)
{
	if (fill_header_map_data(fd, info) == 1)
		return ;
	if (info->number_of_elemnts < 6)
	{
		exitmassege("header data not compleaed\n", info);
		return ;
	}
	if (!info->map)
	{
		exitmassege("No map data\n", info);
		return ;
	}
	after_get_map(info);
	close(fd);
	info->fd = -2;
}
