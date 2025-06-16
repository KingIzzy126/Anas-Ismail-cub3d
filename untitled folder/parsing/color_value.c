/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:50:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/05/16 20:43:22 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**array2d_colors(char **array2d)
{
	char	**new_array2d;
	char	**array2d_split;
	int		i;
	int		j;

	i = 0;
	new_array2d = NULL;
	while (array2d[++i])
	{
		j = 0;
		array2d_split = ft_split(array2d[i], ',');
		while (array2d_split && array2d_split[j])
		{
			new_array2d = add_in_array2d(&new_array2d, array2d_split[j]);
			j++;
		}
		free_array2d(&array2d_split);
	}
	if (len_array2d(new_array2d) != 3)
	{
		if (new_array2d)
			free_array2d(&new_array2d);
		return (NULL);
	}
	return (new_array2d);
}

int	is_valid_range_color(char *str)
{
	int	number_of_color;

	number_of_color = ft_atoi(str);
	if (number_of_color < 0 || number_of_color > 255)
		return (-1);
	return (number_of_color);
}

void	f_value(char **array2d, t_info *info)
{
	char	**new_array2d;

	if (info->floor_color.r != -2)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	if (check_valid_comma(array2d, info) == 1)
		return ;
	new_array2d = array2d_colors(array2d);
	if (!new_array2d)
	{
		exitmassege("three numbers only(r, g, b).\n", info);
		return ;
	}
	info->floor_color.r = is_valid_range_color(new_array2d[0]);
	info->floor_color.g = is_valid_range_color(new_array2d[1]);
	info->floor_color.b = is_valid_range_color(new_array2d[2]);
	if (info->floor_color.r == -1 || info->floor_color.g == -1
		|| info->floor_color.b == -1)
		exitmassege("invalid number, it is must between 0-255\n", info);
	info->number_of_elemnts++;
	if (new_array2d)
		free_array2d(&new_array2d);
}

void	c_value(char **array2d, t_info *info)
{
	char	**new_array2d;

	if (info->ceiling_color.r != -2)
	{
		exitmassege("You have filled it out before.\n", info);
		return ;
	}
	if (check_valid_comma(array2d, info) == 1)
		return ;
	new_array2d = array2d_colors(array2d);
	if (!new_array2d)
	{
		exitmassege("three numbers only(r, g, b).\n", info);
		return ;
	}
	info->ceiling_color.r = is_valid_range_color(new_array2d[0]);
	info->ceiling_color.g = is_valid_range_color(new_array2d[1]);
	info->ceiling_color.b = is_valid_range_color(new_array2d[2]);
	if (info->ceiling_color.r == -1 || info->ceiling_color.g == -1
		|| info->ceiling_color.b == -1)
		exitmassege("invalid number, it is must between 0-255\n", info);
	info->number_of_elemnts++;
	if (new_array2d)
		free_array2d(&new_array2d);
}
