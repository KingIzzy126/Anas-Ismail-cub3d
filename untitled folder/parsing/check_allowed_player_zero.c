/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_allowed_player_zero.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:37:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 16:44:03 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_each_line(int i, t_info *info)
{
	int	j;
	int	previous_len_x;
	int	next_len_x;

	j = 0;
	previous_len_x = -1;
	next_len_x = -1;
	if (i > 0)
		previous_len_x = ft_strlen(info->map[i - 1]) - 1;
	if (info->map[i + 1])
		next_len_x = ft_strlen(info->map[i + 1]) - 1;
	while (info->map[i][j])
	{
		if (info->map[i][j] == '0' || info->map[i][j] == 'N'
			|| info->map[i][j] == 'S' || info->map[i][j] == 'E'
			|| info->map[i][j] == 'W')
		{
			if (previous_len_x < j)
				return (1);
			if (next_len_x < j)
				return (1);
		}
		j++;
	}
	return (0);
}

int	check_zero_player_allowed(t_info *info)
{
	int	i;

	i = 0;
	while (info->map[i])
	{
		if (check_each_line(i, info) == 1)
			return (1);
		i++;
	}
	return (0);
}
