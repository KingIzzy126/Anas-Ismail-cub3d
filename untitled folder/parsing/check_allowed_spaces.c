/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_allowed_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:46:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 20:14:21 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_axis_x(int i, int j, t_info *info)
{
	if (info->map[i][j + 1] && !(info->map[i][j + 1] == ' ' || info->map[i][j
			+ 1] == '1'))
		return (1);
	if (j > 0 && !(info->map[i][j - 1] == ' ' || info->map[i][j - 1] == '1'))
		return (1);
	return (0);
}

int	check_axis_y(int previous_len_x, int i, int j, t_info *info)
{
	int	next_len_x;

	if (i > 0 && previous_len_x >= j && !(info->map[i - 1][j] == ' '
		|| info->map[i - 1][j] == '1'))
		return (1);
	if (info->map[i + 1])
	{
		next_len_x = ft_strlen(info->map[i + 1]) - 1;
		if (next_len_x >= j && info->map[i + 1] && !(info->map[i + 1][j] == ' '
			|| info->map[i + 1][j] == '1'))
			return (1);
	}
	return (0);
}

int	check_each_lines(int previous_len_x, int i, t_info *info)
{
	int	j;

	j = 0;
	while (info->map[i][j])
	{
		if (info->map[i][j] == ' ')
		{
			if (check_axis_x(i, j, info) == 1)
				return (1);
			if (check_axis_y(previous_len_x, i, j, info) == 1)
				return (1);
		}
		j++;
	}
	return (0);
}

int	check_spaces_allowed(t_info *info)
{
	int	i;
	int	previous_len_x;

	i = 0;
	previous_len_x = ft_strlen(info->map[i]) - 1;
	while (info->map[i])
	{
		if (check_each_lines(previous_len_x, i, info) == 1)
			return (1);
		previous_len_x = ft_strlen(info->map[i]) - 1;
		i++;
	}
	return (0);
}
