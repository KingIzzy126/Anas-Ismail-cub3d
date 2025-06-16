/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:07:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 17:08:38 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	chars_data_map(char c, int x, t_info *info)
{
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
			|| c == ' '))
		exitmassege("invalid input in the map\n", info);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (info->is_hv_plr == 1)
			exitmassege("You Have More Than One Player\n", info);
		info->is_hv_plr = 1;
		info->x_plr = x;
		info->y_plr = info->y_lngth_mp - 1;
		info->facing_plr = c;
	}
}

void	data_map(char *test_line_map, t_info *info)
{
	int	x;

	x = 0;
	if (info->is_hv_err == 1)
		return ;
	if (ft_strlen(test_line_map) == 0)
		exitmassege("It Must Not Empety\n", info);
	if (info->is_hv_err == 1)
		return ;
	while (*test_line_map)
	{
		chars_data_map(*test_line_map, x, info);
		test_line_map++;
		x++;
		if (info->is_hv_err == 1)
			return ;
	}
}
